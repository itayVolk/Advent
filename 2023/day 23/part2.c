/* 
   Author: Itay Volk
   Date: 01/11/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef struct node {
    int x;
    int y;
    int num;
    struct node ** next;
} NODE;

int moveX(int x, int d) {
    if (d%2 == 0) {
        return x;
    }
    return x + d - 2;
}

int moveY(int y, int d) {
    if (d%2 == 1) {
        return y;
    }
    return y + d - 1;
}

bool ** paste(bool ** visited, int width, int height) {
    bool ** copy = malloc(height*sizeof(bool *));
    for (int i = 0; i < height; i++) {
        copy[i] = malloc(width*sizeof(bool));
        for (int j = 0 ; j < width; j++) {
            copy[i][j] = visited[i][j];
        }
    }
    return copy;
}

int countDirs(bool ** map, int x, int y) {
    int count = 0;
    for (int d = 0; d < 4; d++) {
        if (!map[moveY(y, d)][moveX(x, d)]) {
            count++;
        }
    }
    return count;
}

int traceDir(bool ** map, int x, int y, int * ox, int * oy, int dir) {
    // printf("%d,%d,%d\n", x, y, dir);
    if (map[y][x]) {
        return -1;
    }
    
    if (countDirs(map, x, y) > 2) {
        *ox = x;
        *oy = y;
        return 0;
    }
    int weight;
    int count = 0;
    for (int d = 0; d < 4; d++) {
        if ((d+2)%4 != dir) {
            int tx, ty;
            int temp = traceDir(map, moveX(x, d), moveY(y, d), ox, oy, d);
            if (temp != -1) {
                count++;
                weight = temp;
            }
        }
    }
    if (count > 1) {
        *ox = x;
        *oy = y;
        return 0;
    }
    return weight+1;
}

int traceGraph(int x, int y, int width, int height, NODE *** nodes, int ** weights, bool ** visited) {
    if (x == width-2 && y == height-2) {
        return 1;
    }
    if(visited[y][x]) {
        return -1;
    }
    visited[y][x] = true;

    int max = 0;
    for (int i = 0; i < nodes[y][x]->num; i++) {
        int tx = nodes[y][x]->next[i]->x;
        int ty = nodes[y][x]->next[i]->y;
        int temp = traceGraph(tx, ty, width, height, nodes, weights, paste(visited, width, height));
        if (temp != -1 && temp + weights[y*width+x][ty*width+tx] > max) {
            max = temp + weights[y*width+x][ty*width+tx];
        }
    }
    return max;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool ** map = malloc(150*sizeof(bool *));
    int height = 0;
    int width;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        map[height] = malloc(width*sizeof(bool));
        for (int i = 0; i < width; i++) {
            map[height][i] = line[i] == '#';
        }
        height++;
    }
    map[0][1] = true;
    map[height-1][width-2] = true;

    int ** weights = malloc(height*width*sizeof(int *));
    for (int i = 0; i < height*width; i++) {
        weights[i] = calloc(width, sizeof(int));
    }
    NODE *** nodes = malloc(height*sizeof(NODE **));
    for (int i = 0; i < height; i++) {
        nodes[i] = malloc(height*width*sizeof(NODE *));
        for (int j = 0; j < width; j++) {
            nodes[i][j] = malloc(sizeof(NODE));
            nodes[i][j]->x = j;
            nodes[i][j]->y = i;
            nodes[i][j]->num = 0;
            nodes[i][j]->next = malloc(4*sizeof(NODE *));
        }
    }

    int ex, ey;
    // printf("start\n");
    int e = traceDir(map, 1, 1, &ex, &ey, 2);
    // printf("end\n");
    weights[width+1][ey*width+ex] = e;
    nodes[1][1]->next[nodes[1][1]->num++] = nodes[ey][ex];
    weights[ey*width+ex][width+1] = e;
    nodes[ey][ex]->next[nodes[ey][ex]->num++] = nodes[1][1];
    e = traceDir(map, width-2, height-2, &ex, &ey, 0);
    // printf("%d\n", e);
    weights[height*width-width-2][ey*width+ex] = e;
    nodes[height-2][width-2]->next[nodes[height-2][width-2]->num++] = nodes[ey][ex];
    weights[ey*width+ex][height*width-width-2] = e;
    nodes[ey][ex]->next[nodes[ey][ex]->num++] = nodes[height-2][width-2];
    // printf("%p\n", weights);
    
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            printf("%d,%d\n", j, i);
            if (!map[i][j] && countDirs(map, j, i) > 2) {
                for (int d = 0; d < 4; d++) {
                    int x, y;
                    int weight = traceDir(map, moveX(j, d), moveY(i, d), &x, &y, d);
                    if (weight != -1) {
                        weights[i*width+j][y*width+x] = weight;
                        nodes[i][j]->next[nodes[i][j]->num++] = nodes[y][x];
                        weights[y*width+x][i*width+j] = weight;
                        nodes[y][x]->next[nodes[y][x]->num++] = nodes[i][j];
                    }
                }
            }
        }
    }
    printf("%p\n", nodes);    
    bool ** visited = malloc(height*sizeof(bool *));
    for (int i = 0; i < height; i++) {
        visited[i] = calloc(width, sizeof(bool));
    }
    printf("%d\n", traceGraph(1, 1, width, height, nodes, weights, visited));
    return 0;
}