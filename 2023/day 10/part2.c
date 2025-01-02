/* 
   Author: Itay Volk
   Date: 01/02/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef enum tile {BLANK, VERT, HORZ, NE, NW, SE, SW} TILE;

typedef struct edge {
    TILE type;
    int x;
    int y;
} EDGE;

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

char tile2char(TILE t) {
    switch (t) {
        case BLANK:
            return '.';
        case VERT:
            return '|';
        case HORZ:
            return '-';
        case NE:
            return 'L';
        case NW:
            return 'J';
        case SE:
            return 'F';
        case SW:
            return '7';
    }
}

void move(int dir, int * x, int * y) {
    if (dir%2 == 0) {
        *x += dir-1;
    } else {
        *y += dir-2;
    }
}

LIST * edgeTrace(int x, int y, int width, int height, int dir, TILE ** map) {
    int sx = x;
    int sy = y;
    LIST * out = createList(NULL);
    move(dir, &x, &y);
    while (x != sx || y != sy) {
        EDGE * add = malloc(sizeof(EDGE));
        add->x = x;
        add->y = y;
        add->type = map[y][x];
        addFirst(out, add);
        switch (map[y][x]) {
            case BLANK:
                return NULL;
            case VERT:
            case HORZ:
                if (dir%2 != map[y][x]%2) {
                    return NULL;
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
                    return NULL;
                }
        }
        move(dir, &x, &y);
    }
    return out;
}

int trace(int x, int y, int width, int height, bool **map) {
    if (map[y][x]) {
        return 0;
    }
    map[y][x] = true;
    int count = x%2&&y%2;
    if (x > 0) {
        if (!map[y][x-1]) {
            int out = trace(x-1, y, width, height, map);
            if (out == -1) {
                count = -1;
            } else if (count != -1){
                count += out;
            }
        }
    } else {
        count = -1;
    }
    if (x < width-1) {
        if (!map[y][x+1]) {
            int out = trace(x+1, y, width, height, map);
            if (out == -1) {
                count = -1;
            } else if (count != -1){
                count += out;
            }
        }
    } else {
        count = -1;
    }
    if (y > 0) {
        if (!map[y-1][x]) {
            int out = trace(x, y-1, width, height, map);
            if (out == -1) {
                count = -1;
            } else if (count != -1){
                count += out;
            }
        }
    } else {
        count = -1;
    }
    if (y < height-1) {
        if (!map[y+1][x]) {
            int out = trace(x, y+1, width, height, map);
            if (out == -1) {
                count = -1;
            } else if (count != -1){
                count += out;
            }
        }
    } else {
        count = -1;
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
        LIST * out = edgeTrace(x, y, width, height, dir, map);
        if (out != NULL) {
            width = 2*width+1;
            height = 2*height+1;
            bool ** counted = malloc(height*sizeof(bool*));
            for (int i = 0; i < height; i++) {
                counted[i] = calloc(width, sizeof(bool));
            }
            EDGE * first = getFirst(out);
            EDGE * last = getLast(out);
            EDGE * add = malloc(sizeof(EDGE));
            add->x = x;
            add->y = y;
            if (first->x == last->x) {
                add->type = VERT;
            } else if (first->y == last->y) {
                add->type = HORZ;
            } else {
                add->type = NE;
                if (first->x == x) {
                    if (last->x < x) {
                        add->type++;
                    }
                    if (first->y > y) {
                        add->type += 2;
                    }
                } else {
                    if (first->x < x) {
                        add->type++;
                    }
                    if (last->y > y) {
                        add->type += 2;
                    }
                }
            }
            addLast(out, add);
            while (numItems(out) > 0) {
                EDGE * tile = removeFirst(out);
                tile->x = 2*tile->x+1;
                tile->y = 2*tile->y+1;
                int tx = tile->x;
                int ty = tile->y;
                counted[ty][tx] = true;
                int d1 = 0;
                int d2 = 0;
                switch (tile->type) {
                    case BLANK:
                        break;
                    case VERT:
                    case HORZ:
                        d1 = tile->type%2;
                        d2 = tile->type%2+2;
                        break;
                    case NE:
                    case NW:
                    case SE:
                    case SW:
                        d1 = tile->type%2*2;
                        d2 = 1+(tile->type-3)/2*2;
                        break;
                }
                move(d1, &tx, &ty);
                counted[ty][tx] = true;
                tx = tile->x;
                ty = tile->y;
                move(d2, &tx, &ty);
                counted[ty][tx] = true;
            }

            int total = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (i%2 && j%2 && !counted[i][j]) {
                        int cur = trace(j, i, width, height, counted);
                        if (cur != -1) {
                            total += cur;
                        }
                    }
                }
            }
            printf("%d\n", total);
            
            return 0;
        }
        dir++;
    }
    printf("no loop\n");
    return -1;
}