/* 
   Author: Itay Volk
   Date: 01/02/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum tile {BLANK, VERT, HORZ, NE, NW, SE, SW} TILE;

TILE char2tile(char c) {
    switch (c) {
        case '.':
            return BLANK;
        case '|':
            return VERT;
        case '-':
            return HORZ;
        case 'L':
            return NE;
        case 'J':
            return NW;
        case 'F':
            return SE;
        case '7':
            return SW;
    }
    return BLANK;
}

void move(int dir, int * x, int * y) {
    if (dir%2 == 0) {
        *x += dir-1;
    } else {
        *y += dir-2;
    }
}

int trace(int x, int y, int width, int height, int dir, TILE ** map) {
    int sx = x;
    int sy = y;
    int count = 0;
    move(dir, &x, &y);
    while (x != sx || y != sy) {
        count++;
        switch (map[y][x]) {
            case BLANK:
                return -1;
            case VERT:
            case HORZ:
                if (dir%2 != map[y][x]%2) {
                    return -1;
                }
                break;
            case NE:
            case NW:
            case SE:
            case SW:
                if (dir == 3-(map[y][x]-3)/2*2) {
                    dir = map[y][x]%2*2;
                } else if (dir == (map[y][x]-1)%2*2) {
                    dir = 1+(map[y][x]-3)/2*2;
                } else {
                    return -1;
                }
        }
        move(dir, &x, &y);
    }
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    TILE ** map = malloc(150*sizeof(TILE *));
    int x = -1;
    int y = -1;
    int height = 0;
    int width = -1;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == -1) {
            width = strlen(line)-1;
        }
        map[height] = calloc(width, sizeof(TILE));
        for (int i = 0; i < width; i++) {
            if (line[i] == 'S') {
                x = i;
                y = height;
            }
            map[height][i] = char2tile(line[i]);
        }
        height++;
    }
    int dir = 0;
    while (dir < 4) {
        int count = trace(x, y, width, height, dir, map);
        if (count != -1) {
            printf("%d\n", count/2+1);
            return 0;;
        }
        dir++;
    }
    return -1;
}