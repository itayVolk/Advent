/* 
   Author: Itay Volk
   Date: 12/17/2024
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
    int score;
} LOC;

static int compare(LOC * a, LOC * b) {
    return (a->score < b->score) ? -1 : (a->score > b->score);
}

static int same(LOC * a, LOC * b) {
    return a->x != b->x || a->y != b->y;
}

int main() {
    int height = 71;
    int width = 71;
    int count = 1024;

    FILE * fp = fopen("input.txt", "r");
    char line[256];
    int ** arr = malloc(70*sizeof(int*));
    for (int i = 0; i < height; i++) {
        arr[i] = calloc(width, sizeof(int));
    }

    while(count > 0 && fgets(line, sizeof(line), fp) != NULL) {
        char * tok = strtok(line, ",");
        arr[atoi(strtok(NULL, ","))][atoi(tok)] = -1;
        count--;
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
        int x = atoi(strtok(line, ","));
        int y = atoi(strtok(NULL, ","));
        printf("%d,%d\n", x, y);
        arr[y][x] = -1;
        PQ * q = createQueue(compare);
        LIST * spent = createList(same);
        LOC * cur = malloc(sizeof(LOC));
        cur->x = 0;
        cur->y = 0;
        cur->score = 0;
        addEntry(q, cur);
        while(cur->y != height-1 || cur->x != width-1) {
            if (cur->x+1 < width && arr[cur->y][cur->x+1] == 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = cur->x+1;
                add->y = cur->y;
                add->score = cur->score+1;
                addEntry(q, add);
            }
            if (cur->x-1 >= 0 && arr[cur->y][cur->x-1] == 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = cur->x-1;
                add->y = cur->y;
                add->score = cur->score+1;
                addEntry(q, add);
            }
            if (cur->y+1 < height && arr[cur->y+1][cur->x] == 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = cur->x;
                add->y = cur->y+1;
                add->score = cur->score+1;
                addEntry(q, add);
            }
            if (cur->y-1 >= 0 && arr[cur->y-1][cur->x] == 0) {
                LOC * add = malloc(sizeof(LOC));
                add->x = cur->x;
                add->y = cur->y-1;
                add->score = cur->score+1;
                addEntry(q, add);
            }
            
            do {
                if (numEntries(q) == 0) {
                    printf("%d,%d\n", x, y);
                    return 0;
                }
                cur = removeEntry(q);
                LOC * found = findItem(spent, cur);
                if (found != NULL) {
                    if (found->score > cur->score) {
                        removeItem(spent, found);
                        addFirst(spent, cur);
                        break;
                    }
                } else {
                    addFirst(spent, cur);
                    break;
                }
            } while(true);
        }
    }
    return 0;
}