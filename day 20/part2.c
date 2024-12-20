/* 
   Author: Itay Volk
   Date: 12/19/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pqueue.h"

typedef struct loc {
    int x;
    int y;
    int score;
} LOC;

static int compare(LOC * a, LOC * b) {
    return (a->score < b->score) ? -1 : (a->score > b->score);
}

void expand(LOC * cur, int width, int height, int ** arr, PQ * q) {
    if (cur->x+1 < width && arr[cur->y][cur->x+1] >= 0) {
        LOC * add = malloc(sizeof(LOC));
        add->x = cur->x+1;
        add->y = cur->y;
        add->score = cur->score+1;
        addEntry(q, add);
    }
    if (cur->x-1 >= 0 && arr[cur->y][cur->x-1] >= 0) {
        LOC * add = malloc(sizeof(LOC));
        add->x = cur->x-1;
        add->y = cur->y;
        add->score = cur->score+1;
        addEntry(q, add);
    }
    if (cur->y+1 < height && arr[cur->y+1][cur->x] >= 0) {
        LOC * add = malloc(sizeof(LOC));
        add->x = cur->x;
        add->y = cur->y+1;
        add->score = cur->score+1;
        addEntry(q, add);
    }
    if (cur->y-1 >= 0 && arr[cur->y-1][cur->x] >= 0) {
        LOC * add = malloc(sizeof(LOC));
        add->x = cur->x;
        add->y = cur->y-1;
        add->score = cur->score+1;
        addEntry(q, add);
    }
}

int ** trace(int x, int y, int width, int height, int ** arr) {
    PQ * q = createQueue(compare);
    int ** vals = malloc(height*sizeof(int*));
    for (int i = 0; i < height; i++) {
        vals[i] = malloc(width*sizeof(int));
        for (int j = 0; j < width; j++) {
            vals[i][j] = -1;
        }
    }
    LOC * cur = malloc(sizeof(LOC));
    cur->x = x;
    cur->y = y;
    cur->score = 0;
    addEntry(q, cur);
    while(cur != NULL) {
        expand(cur, width, height, arr, q);
        do {
            cur = removeEntry(q);
            if (vals[cur->y][cur->x] == -1 || vals[cur->y][cur->x] > cur->score) {
                vals[cur->y][cur->x] = cur->score;
                break;
            }
            if (numEntries(q) == 0) {
                cur = NULL;
                break;
            }
        } while(true);
    }
    return vals;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int y = 0;
    int x = 0;
    int ye = 0;
    int xe = 0;

    int ** arr = malloc(200*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line)-1;
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            if (line[i] == '#') {
                arr[height][i] = -1;
            } else if (line[i] == 'S') {
                y = height;
                x = i;
            } else if (line[i] == 'E') {
                ye = height;
                xe = i;
            }
        }
        height++;
    }

    int ** dist = trace(x, y, width, height, arr);
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] == 0 && dist[i][j] != -1) {
                for (int ji = 0; ji < height; ji++) {
                    for (int jj = 0; jj < width; jj++) {
                        int jump = abs(i-ji)+abs(j-jj);
                        if (arr[i][j] == 0 && dist[i][j] != -1 && jump <= 20 && dist[ji][jj]-dist[i][j]-jump >= 100) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}