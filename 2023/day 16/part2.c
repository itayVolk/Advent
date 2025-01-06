/* 
   Author: Itay Volk
   Date: 01/05/2025
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tile {BLANK, VERT, HORIZ, FRWD, BACK} TILE;

TILE char2tile(char c) {
    switch (c) {
        case '.':
            return BLANK;
        case '|':
            return VERT;
        case '-':
            return HORIZ;
        case '/':
            return FRWD;
        case '\\':
            return BACK;
    }
    return BLANK;
}

void move (int * x, int * y, int dir) {
    if (dir%2 == 0) {
        *x += dir-1;
    } else {
        *y += dir-2;
    }
}

int trace(int x, int y, int dir, int width, int height, TILE ** map, int ** energized) {
    move(&x, &y, dir);
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return 0;
    }
    if (energized[y][x]&(int)pow(2, dir)) {
        return 0;
    }
    int count = !energized[y][x];
    energized[y][x] += pow(2, dir);

    if (map[y][x] == VERT || map[y][x] == HORIZ) {
        if (dir%2 != map[y][x]) {
            count += trace(x, y, map[y][x], width, height, map, energized);
            count += trace(x, y, (map[y][x]+2)%4, width, height, map, energized);
            return count;
        }
    } else if (map[y][x] == FRWD || map[y][x] == BACK) {
        dir++;
        dir += (map[y][x]+dir%2+1)%2*2;
        dir = dir%4;
    }
    return count + trace(x, y, dir, width, height, map, energized);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    TILE ** map = malloc(150*sizeof(TILE *));
    int height = 0;
    int width;
    
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        map[height] = calloc(width, sizeof(TILE));
        for (int i = 0; i < width; i++) {
            map[height][i] = char2tile(line[i]);
        }
        height++;
    }

    int max = 0;

    for (int i = 0; i < height; i++) {
        int ** energized = malloc(height*sizeof(int *));
        for (int i = 0; i < height; i++) {
            energized[i] = calloc(width, sizeof(int));
        }

        int test = trace(0, i, 2, width, height, map, energized);
        if (test > max) {
            max = test;
        }
        test = trace(width-1, i, 0, width, height, map, energized);
        if (test > max) {
            max = test;
        }
    }
    for (int i = 0; i < width; i++) {
        int ** energized = malloc(height*sizeof(int *));
        for (int i = 0; i < height; i++) {
            energized[i] = calloc(width, sizeof(int));
        }

        int test = trace(i, 0, 3, width, height, map, energized);
        if (test > max) {
            max = test;
        }
        test = trace(i, height-1, 1, width, height, map, energized);
        if (test > max) {
            max = test;
        }
    }
    printf("%d\n", max);
    return 0;
}