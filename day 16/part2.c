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
    LIST * prev;
} LOC;

static int compare(LOC * a, LOC * b) {
    return (a->score < b->score) ? -1 : (a->score > b->score);
}

static int same(LOC * a, LOC * b) {
    return a->x != b->x || a->y != b->y || a->dir != b->dir;
}

static int loc(LOC * a, LOC * b) {
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

int trace(LOC * prev, LIST * traced) {
    int total = 1;
    printf("%d:%d:%d\n", prev->x, prev->y, numItems(prev->prev));
    while(numItems(prev->prev) > 0) {
        LOC * temp = removeFirst(prev->prev);
        if (findItem(traced, temp) == NULL) {
            addFirst(traced, temp);
            total += trace(temp, traced);
        }
    }
    return total;
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
    cur->prev = createList(same);
    addEntry(q, cur);
    addFirst(spent, cur);
    // int path = 0;
    // int count = 0;
    LOC * reached = NULL;
    while(reached == NULL || cur->score == reached->score) {//TODO add a way to see everything that led to a path (likely a list for prev)
        if (arr[cur->y][cur->x] == 1) {
            reached = cur;
        } else {
            printf("%d\n", arr[cur->y][cur->x]);
            if (moveX(cur->x, cur->dir) >= 0 && moveX(cur->x, cur->dir) < width && moveY(cur->y, cur->dir) >= 0 && moveY(cur->y, cur->dir) < height && arr[moveY(cur->y, cur->dir)][moveX(cur->x, cur->dir)] >= 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = moveX(cur->x, cur->dir);
                add->y = moveY(cur->y, cur->dir);
                if (add->x == 5 && add->y == 7) {
                    printf("hit\n");
                }
                add->dir = cur->dir;
                add->score = cur->score+1;
                printf("m");
                LOC * exist = findItem(spent, add);
                printf("%p\n", exist);
                if (exist == NULL) {
                    add->prev = createList(same);
                    addFirst(add->prev, cur);
                    addEntry(q, add);
                    addFirst(spent, add);
                } else if (add->score == exist->score){
                    addFirst(exist->prev, cur);
                } else {
                    printf("d%d:%d:%d:%d:%d:%d\n", add->score-exist->score, add->x, add->y, add->dir, exist->dir, add->score);
                }
            }
            LOC * add = malloc(sizeof(LOC));
            add->dir = (cur->dir+1)%4;
            if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
                add->x = moveX(cur->x, add->dir);
                add->y = moveY(cur->y, add->dir);
                add->score = cur->score+1001;
                LOC * exist = findItem(spent, add);
                printf("%p\n", exist);
                if (exist == NULL) {
                    add->prev = createList(same);
                    addFirst(add->prev, cur);
                    addEntry(q, add);
                    addFirst(spent, add);
                } else if (add->score == exist->score){
                    addFirst(exist->prev, cur);
                } else {
                    printf("d%d:%d:%d:%d:%d:%d\n", add->score-exist->score, add->x, add->y, add->dir, exist->dir, add->score);
                }
            }
            add = malloc(sizeof(LOC));
            add->dir = (cur->dir+3)%4;
            if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
                add->x = moveX(cur->x, add->dir);
                add->y = moveY(cur->y, add->dir);
                add->score = cur->score+1001;
                LOC * exist = findItem(spent, add);
                printf("%p\n", exist);
                if (exist == NULL) {
                    add->prev = createList(same);
                    addFirst(add->prev, cur);
                    addEntry(q, add);
                    addFirst(spent, add);
                } else if (add->score == exist->score){
                    addFirst(exist->prev, cur);
                } else {
                    printf("d%d:%d:%d:%d:%d:%d\n", add->score-exist->score, add->x, add->y, add->dir, exist->dir, add->score);
                }
            }
        }
        printf("%d:%d:%d:%d:%d:%d\n", cur->x, cur->y, cur->dir, arr[cur->y][cur->x], cur->score, numEntries(q));
        assert(cur->dir >= 0 && cur->dir < 4);
        cur = removeEntry(q);
    }
    printf("%d\n", reached->score);
    printf("%d\n", trace(reached, createList(loc)));
    return 0;
}