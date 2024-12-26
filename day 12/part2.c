/* 
   Author: Itay Volk
   Date: 12/12/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int dir;
    int start;
    int end;
    int stable;
    struct node * next;
} NODE;

void insertEdge(NODE * edges, int dir, int x, int y) {
    NODE * temp = malloc(sizeof(NODE));
    temp->next = edges->next;
    edges->next = temp;
    temp->dir = dir;
    if (dir%2 == 0) {
        temp->stable = y;
        temp->start = x;
        temp->end = x;
    } else {
        temp->stable = x;
        temp->start = y;
        temp->end = y;
    }
}

int minimum(int a, int b) {
    return a < b ? a : b;
}

int maximum(int a, int b) {
    return a > b ? a : b;
}

void mergeEdges (NODE * a, NODE * b, NODE * bpre) {
    a->start = minimum(a->start, b->start);
    a->end = maximum(a->end, b->end);
    bpre->next = b->next;
    free(b);
}

void edgeCheck(NODE * edges, int dir, int x, int y) {
    NODE * prev = edges;
    NODE * inside = NULL;
    edges = edges->next;
    while (edges != NULL) {
        if (edges->dir == dir) {
            if (dir%2 == 0) {
                if (y == edges->stable) {
                    if (x == edges->start-1) {
                        edges->start--;
                    } else if (x == edges->end+1) {
                        edges->end++;
                    }
                    if (edges->start <= x && x <= edges->end) {
                        if (inside == NULL) {
                            inside = edges;
                        } else {
                            mergeEdges(inside, edges, prev);
                        }
                    }
                }
            } else {
                if (x == edges->stable) {
                    if (y == edges->start-1) {
                        edges->start--;
                    } else if (y == edges->end+1) {
                        edges->end++;
                    }
                    if (edges->start <= y && y <= edges->end) {
                        if (inside == NULL) {
                            inside = edges;
                        } else {
                            mergeEdges(inside, edges, prev);
                        }
                    }
                }
            }
        }
        prev = edges;
        edges = edges->next;
    }
    if (inside == NULL) {
        insertEdge(prev, dir, x, y);
    }
}

int trace(int x, int y, int width, int height, bool **counted, int ** map, NODE * edges) {
    if (counted[y][x]) {
        return 0;
    }
    counted[y][x] = true;
    int count = 1;
    if (x > 0) {
        if (map[y][x-1] == map[y][x]) {
            count += trace(x-1, y, width, height, counted, map, edges);
        } else {
            edgeCheck(edges, 1, x, y);
        }
    } else {
        edgeCheck(edges, 1, x, y);
    }
    if (x < width-1) {
        if (map[y][x+1] == map[y][x]) {
            count += trace(x+1, y, width, height, counted, map, edges);
        } else {
            edgeCheck(edges, 3, x, y);
        }
    } else {
        edgeCheck(edges, 3, x, y);
    }
    if (y > 0) {
        if (map[y-1][x] == map[y][x]) {
            count += trace(x, y-1, width, height, counted, map, edges);
        } else {
            edgeCheck(edges, 0, x, y);
        }
    } else {
        edgeCheck(edges, 0, x, y);
    }
    if (y < height-1) {
        if (map[y+1][x] == map[y][x]) {
            count += trace(x, y+1, width, height, counted, map, edges);
        } else {
            edgeCheck(edges, 2, x, y);
        }
    } else {
        edgeCheck(edges, 2, x, y);
    }
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int y = 0;
    int x = 0;

    int ** arr = malloc(150*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line)-1;
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            arr[height][i] = line[i]-'A';
        }
        height++;
    }

    bool ** counted = malloc(height*sizeof(bool*));
    for (int i = 0; i < height; i++) {
        counted[i] = calloc(width, sizeof(bool));
    }

    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!counted[i][j]) {
                NODE * edges = malloc(sizeof(NODE));
                edges->dir = -1;
                edges->next = NULL;
                int area = trace(j, i, width, height, counted, arr, edges);

                int count = 0;
                edges = edges->next;
                while(edges != NULL) {
                    count++;
                    edges = edges->next;
                }
                sum += area * count;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}