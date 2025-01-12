/* 
   Author: Itay Volk
   Date: 01/11/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

typedef struct node {
    int x;
    int y;
    int id;
} NODE;

static int compare(NODE * a, NODE * b) {
    return a->x != b->x || a->y != b->y;
}

static unsigned hash(NODE * a) {
    return a->x + a->y;
}

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

bool * paste(bool * visited, int num) {
    bool * copy = malloc(num*sizeof(bool));
    for (int i = 0; i < num; i++) {
        copy[i] = visited[i];
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
    if (countDirs(map, x, y) != 2) {
        *ox = x;
        *oy = y;
        return 1;
    }
    for (int d = 0; d < 4; d++) {
        if ((d+2)%4 != dir && !map[moveY(y, d)][moveX(x, d)]) {
            return traceDir(map, moveX(x, d), moveY(y, d), ox, oy, d)+1;
        }
    }
    return -1;
}

int traceGraph(int i, int num, NODE ** nodes, int ** weights, bool * visited) {
    if (i == num-1) {
        return 1;
    }
    visited[i] = true;

    int max = -1;
    for (int j = 0; j < num; j++) {
        if (i != j && weights[i][j] != 0 && !visited[j]) {
            int temp = traceGraph(j, num, nodes, weights, paste(visited, num));
            if (temp != -1 && temp + weights[i][j] > max) {
                max = temp + weights[i][j];
            }
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

    NODE ** nodes = malloc(height*width*sizeof(NODE *));
    int num = 0;
    SET * table = createSet(height*width, compare, hash);
    
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            if (!map[i][j] && countDirs(map, j, i) != 2) {
                NODE * add = malloc(sizeof(NODE));
                add->x = j;
                add->y = i;
                add->id = num;
                nodes[num++] = add;
                addElement(table, add);
            }
        }
    }

    int ** weights = malloc(num*sizeof(int *));
    for (int i = 0; i < num; i++) {
        weights[i] = calloc(num, sizeof(int));
    }
    for (int i = 0; i < num; i++) {
        for (int d = 0; d < 4; d++) {
            if (!map[moveY(nodes[i]->y, d)][moveX(nodes[i]->x, d)]) {
                int x, y;
                int weight = traceDir(map, moveX(nodes[i]->x, d), moveY(nodes[i]->y, d), &x, &y, d);
                NODE * search = malloc(sizeof(NODE));
                search->x = x;
                search->y = y;
                search = findElement(table, search);
                weights[nodes[i]->id][search->id] = weight;
            }
        }
    }
    printf("%d\n", 1+traceGraph(0, num, nodes, weights, calloc(num, sizeof(bool))));
    return 0;
}