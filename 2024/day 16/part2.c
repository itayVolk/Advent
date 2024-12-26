/* 
   Author: Itay Volk
   Date: 12/15/2024
*/

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
    int total = 0;
    while(numItems(prev->prev) > 0) {
        LOC * temp = removeFirst(prev->prev);
        if (findItem(traced, temp) == NULL) {
            addFirst(traced, temp);
            total++;
        }
        total += trace(temp, traced);
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
    while(arr[cur->y][cur->x] != 1) {
        if (moveX(cur->x, cur->dir) >= 0 && moveX(cur->x, cur->dir) < width && moveY(cur->y, cur->dir) >= 0 && moveY(cur->y, cur->dir) < height && arr[moveY(cur->y, cur->dir)][moveX(cur->x, cur->dir)] >= 0) {
            LOC * add = malloc(sizeof(LOC));
            add->x = moveX(cur->x, cur->dir);
            add->y = moveY(cur->y, cur->dir);
            add->dir = cur->dir;
            add->score = cur->score+1;
            addEntry(q, add);
            add->prev = createList(same);
            addFirst(add->prev, cur);
        }
        LOC * add = malloc(sizeof(LOC));
        add->dir = (cur->dir+1)%4;
        if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
            add->x = moveX(cur->x, add->dir);
            add->y = moveY(cur->y, add->dir);
            add->score = cur->score+1001;
            addEntry(q, add);
            add->prev = createList(same);
            addFirst(add->prev, cur);
        }
        add = malloc(sizeof(LOC));
        add->dir = (cur->dir+3)%4;
        if (moveX(cur->x, add->dir) >= 0 && moveX(cur->x, add->dir) < width && moveY(cur->y, add->dir) >= 0 && moveY(cur->y, add->dir) < height && arr[moveY(cur->y, add->dir)][moveX(cur->x, add->dir)] >= 0) {
            add->x = moveX(cur->x, add->dir);
            add->y = moveY(cur->y, add->dir);
            add->score = cur->score+1001;
            addEntry(q, add);
            add->prev = createList(same);
            addFirst(add->prev, cur);
        }
        do {
            cur = removeEntry(q);
            LOC * found = findItem(spent, cur);
            if (found != NULL) {
                if (found->score > cur->score) {
                    removeItem(spent, found);
                    addFirst(spent, cur);
                    break;
                } else if (found->score == cur->score) {
                    while (numItems(cur->prev) > 0) {
                        LOC * temp = removeFirst(cur->prev);
                        if (findItem(found->prev, temp) == NULL) {
                            addFirst(found->prev, temp);
                        }
                    }
                }
            } else {
                addFirst(spent, cur);
                break;
            }
        } while(true);
    }

    printf("%d\n", 1+trace(cur, createList(loc)));
    return 0;
}