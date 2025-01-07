/* 
   Author: Itay Volk
   Date: 12/15/2024
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

typedef struct loc {
    int x;
    int y;
    int dir;
    int dist;
    int score;
} LOC;

static int compare(LOC * a, LOC * b) {
    return (a->score < b->score) ? -1 : (a->score > b->score) ? 1 : (a->x+a->y < b->x+b->y) ? 1 : -(a->x+a->y > b->x+b->y);
}

int moveX(int x, int dir) {
    if (dir%2 == 0) {
        return x;
    }
    return x+dir-2;
}

int moveY(int y, int dir) {
    if (dir%2 == 1) {
        return y;
    }
    return y+dir-1;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int ** arr = malloc(200*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line)-1;
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            arr[height][i] = line[i]-'0';
        }
        height++;
    }

    int **** cash = malloc(height*sizeof(int ***));
    for (int i = 0; i < height; i++) {
        cash[i] = malloc(width*sizeof(int **));
        for (int j = 0; j < width; j++) {
            cash[i][j] = malloc(10*sizeof(int *));
            for (int k = 0; k < 10; k++) {
                cash[i][j][k] = malloc(4*sizeof(int));
                for (int l = 0; l < 4; l++) {
                    cash[i][j][k][l] = INT_MAX;
                }
            }
        }
    }
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 4; j++) {
            cash[0][0][i][j] = 0;
        }
    }

    PQ * q = createQueue(compare);
    LOC * cur = malloc(sizeof(LOC));
    cur->x = 0;
    cur->y = 0;
    cur->dir = 3;
    cur->dist = 0;
    cur->score = 0;
    addEntry(q, cur);
    while(cur->y != height-1 || cur->x != width-1 || cur->dist < 3) {
        // printf("%d\n", cur->score);
        LOC * add = malloc(sizeof(LOC));
        add->x = moveX(cur->x, cur->dir);
        add->y = moveY(cur->y, cur->dir);
        add->dir = cur->dir;
        add->dist = cur->dist+1;
        if (add->dist < 10 && add->x >= 0 && add->x < width && add->y >= 0 && add->y < height) {
            add->score = cur->score+arr[add->y][add->x];
            addEntry(q, add);
        }
        if (cur->dist >= 3) {
            add = malloc(sizeof(LOC));
            add->dir = (cur->dir+1)%4;
            add->x = moveX(cur->x, add->dir);
            add->y = moveY(cur->y, add->dir);
            add->dist = 0;
            if (add->x >= 0 && add->x < width && add->y >= 0 && add->y < height) {
                add->score = cur->score+arr[add->y][add->x];
                addEntry(q, add);
            }
            add = malloc(sizeof(LOC));
            add->dir = (cur->dir+3)%4;
            add->x = moveX(cur->x, add->dir);
            add->y = moveY(cur->y, add->dir);
            add->dist = 0;
            if (add->x >= 0 && add->x < width && add->y >= 0 && add->y < height) {
                add->score = cur->score+arr[add->y][add->x];
                addEntry(q, add);
            }
        }
        do {
            cur = removeEntry(q);
        } while(cur->score >= cash[cur->y][cur->x][cur->dist][cur->dir]);
        cash[cur->y][cur->x][cur->dist][cur->dir] = cur->score;
    }
    printf("%d\n", cur->score);
    return 0;
}