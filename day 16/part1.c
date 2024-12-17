/* 
   Author: Itay Volk
   Date: 12/15/2024
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pqueue.h"
#include "list.h"

typedef struct loc {
    int x;
    int y;
    int dir;
    int score;
    struct loc * prev;
} LOC;

static int compare(LOC * a, LOC * b) {
    return (a->score < b->score) ? -1 : (a->score > b->score);
}

static int same(LOC * a, LOC * b) {
    return a->x != b->x || a->y != b->y;
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

    int y = 0;
    int x = 0;

    int ** arr = malloc(200*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line);
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            if (line[i] == '#') {
                arr[height][i] = -1;
            } else if (line[i] == 'S') {
                y = height;
                x = i;
            } else if (line[i] == 'E') {
                arr[height][i] = 1;
            }
        }
        height++;
    }

    PQ * q = createQueue(compare);
    LIST * spent = createList(same);
    LOC * cur = malloc(sizeof(LOC));
    cur->x = x;
    cur->y = y;
    cur->dir = 3;
    cur->score = 0;
    cur->prev = NULL;
    addEntry(q, cur);
    addFirst(spent, cur);
    LOC * reached = NULL;
    while(reached == NULL || cur->score <= reached->score) {//TODO try to find the reason why its too big by 12
        if (arr[cur->y][cur->x] == 1) {
            reached = cur;
        } else {
            if (moveX(cur->x, cur->dir) >= 0 && moveX(cur->x, cur->dir) < width && moveY(cur->y, cur->dir) >= 0 && moveY(cur->y, cur->dir) < height && arr[moveY(cur->y, cur->dir)][moveX(cur->x, cur->dir)] >= 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = moveX(cur->x, cur->dir);
                add->y = moveY(cur->y, cur->dir);
                add->dir = cur->dir;
                add->score = cur->score+1;
                add->prev = cur;
                // printf("%p", findItem(spent, add));
                if (findItem(spent, add) == NULL) {
                    addEntry(q, add);
                    addFirst(spent, add);
                }
            }
            LOC * add = malloc(sizeof(LOC));
            add->dir = (cur->dir+1)%4;
            if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
                add->x = moveX(cur->x, add->dir);
                add->y = moveY(cur->y, add->dir);
                add->score = cur->score+1001;
                add->prev = cur;
                if (findItem(spent, add) == NULL) {
                    addEntry(q, add);
                    addFirst(spent, add);
                }
            }
            add = malloc(sizeof(LOC));
            add->dir = (cur->dir+3)%4;
            if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
                add->x = moveX(cur->x, add->dir);
                add->y = moveY(cur->y, add->dir);
                add->score = cur->score+1001;
                add->prev = cur;
                if (findItem(spent, add) == NULL) {
                    addEntry(q, add);
                    addFirst(spent, add);
                }
            }
        }
        printf("%d:%d:%d:%d\n", cur->x, cur->y, arr[cur->y][cur->x], cur->score);
        // assert(arr[cur->y][cur->x] == 0);
        cur = removeEntry(q);
    }
    printf("%d\n", reached->score);

    char ** draw = malloc(height*sizeof(char*));
    for (int i = 0; i < height; i++) {
        draw[i] = calloc(width, sizeof(char));
    }

    LOC * next = reached;
    cur = reached->prev;
    while (cur != NULL) {
        // printf("%d:%d:%d:%d:%d\n", cur->x, cur->y, cur->dir, arr[cur->y][cur->x], cur->score);
        printf("%d\n", cur->score);
        assert((cur->dir==next->dir && cur->score-next->score==-1) || cur->score==next->score-1001);
        assert(abs(cur->y-next->y) + abs(cur->x-next->x) == 1);
        char dir;
        switch (cur->dir) {
            case 0:
                dir = '^';
                break;
            case 1:
                dir = '<';
                break;
            case 2:
                dir = 'v';
                break;
            case 3:
                dir = '>';
                break;
        }
        assert(draw[cur->y][cur->x] == 0);
        draw[cur->y][cur->x] = dir;
        next = cur;
        cur = cur->prev;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (draw[i][j] != '\0') {
                printf("%c", draw[i][j]);
            } else if (arr[i][j]) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}