/* 
   Author: Itay Volk
   Date: 01/22/2025
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pqueue.h"

typedef struct node {
    int x;
    int y;
    int dist;
} NODE;

static int compare(NODE * a, NODE * b) {
    return a->dist-b->dist;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int ** heights = malloc(50*sizeof(int *));
    int height = 0;
    int width;
    int sx, sy, ex, ey;

    while (fgets(line, sizeof(line), fp)) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        heights[height] = malloc(width*sizeof(int));
        for (int i = 0; i < width; i++) {
            heights[height][i] = line[i]-'a';
            if (line[i] == 'S') {
                sx = i;
                sy = height;
                heights[height][i] = 0;
            } else if (line[i] == 'E') {
                ex = i;
                ey = height;
                heights[height][i] = 'z'-'a';
            }
        }
        height++;
    }

    int ** dist = malloc(height*sizeof(int *));
    for (int i = 0; i < height; i++) {
        dist[i] = malloc(width*sizeof(int));
        for (int j = 0; j < width; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    dist[sy][sx] = 0;
    NODE * cur = malloc(sizeof(NODE));
    cur->dist = 0;
    cur->x = sx;
    cur->y = sy;
    PQ * queue = createQueue(compare);
    addEntry(queue, cur);

    while (cur->x != ex || cur->y != ey) {
        if (cur->x > 0 && heights[cur->y][cur->x-1] <= heights[cur->y][cur->x]+1) {
            NODE * add = malloc(sizeof(NODE));
            add->x = cur->x-1;
            add->y = cur->y;
            add->dist = cur->dist+1;
            addEntry(queue, add);
        }
        if (cur->y > 0 && heights[cur->y-1][cur->x] <= heights[cur->y][cur->x]+1) {
            NODE * add = malloc(sizeof(NODE));
            add->x = cur->x;
            add->y = cur->y-1;
            add->dist = cur->dist+1;
            addEntry(queue, add);
        }
        if (cur->x < width-1 && heights[cur->y][cur->x+1] <= heights[cur->y][cur->x]+1) {
            NODE * add = malloc(sizeof(NODE));
            add->x = cur->x+1;
            add->y = cur->y;
            add->dist = cur->dist+1;
            addEntry(queue, add);
        }
        if (cur->y < height-1 && heights[cur->y+1][cur->x] <= heights[cur->y][cur->x]+1) {
            NODE * add = malloc(sizeof(NODE));
            add->x = cur->x;
            add->y = cur->y+1;
            add->dist = cur->dist+1;
            addEntry(queue, add);
        }

        do {
            cur = removeEntry(queue);
        } while(dist[cur->y][cur->x] <= cur->dist);
        dist[cur->y][cur->x] = cur->dist;
    }
    printf("%d\n", cur->dist);
    return 0;
}