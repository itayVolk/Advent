/* 
   Author: Itay Volk
   Date: 01/25/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

#define STORE 30

typedef struct hash {
    int * push;
    long long index;
    long long height;
} HASH;

static int compare (HASH * a, HASH * b) {
    for (int i = 0; i < STORE; i++) {
        if (a->push[i] != b->push[i]) {
            return 1;
        }
    }
    return a->index%5 != b->index%5;
}

static unsigned hash(HASH * h) {
    unsigned hash = 0;
    for (int i = 0; i < STORE; i++) {
        hash += h->push[i];
    }
    return hash;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[12000];
    fgets(line, sizeof(line), fp);
    bool * push = malloc((strlen(line)-1)*sizeof(bool));
    for (int i = 0; i < strlen(line)-1; i++) {
        push[i] = line[i]=='>';
    }

    bool ** map = malloc(100000*sizeof(bool *));
    for (int i = 0; i < 100000; i++) {
        map[i] = calloc(7, sizeof(bool));
    }

    int rocks[5][5][2] = {{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, -1}},
                        {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
                        {{2, 2}, {1, 2}, {0, 0}, {0, 1}, {0, 2}},
                        {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {-1, -1}},
                        {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {-1, -1}}};

    long long height = 0;
    int w = 0;
    bool drop = true;
    int * prev = calloc(STORE, sizeof(int));
    SET * hashed = createSet(100000000, compare, hash);
    for (long long i = 0; i < 1000000000000; i++) {
        HASH * cur = malloc(sizeof(HASH));
        cur->push = calloc(STORE, sizeof(int));
        cur->push[0] = prev[0];
        for (int j = 1; j < STORE; j++) {
            prev[j-1] = prev[j];
            cur->push[j] = prev[j];
        }
        prev[STORE-1] = w%(strlen(line)-1);
        cur->index = i;
        cur->height = height;
        HASH * found = findElement(hashed, cur);
        if (found) {
            long long stop = 0;
            if ((1000000000000-found->index)%(cur->index-found->index)) {
                stop = found->index + (1000000000000-found->index)%(cur->index-found->index);
                HASH ** arr = getElements(hashed);
                for (int j = 0; j < numElements(hashed); j++) {
                    if (arr[j]->index == stop) {
                        stop = arr[j]->height-found->height;
                        break;
                    }
                }
            }
            printf("%lld\n", stop + found->height + (1000000000000-found->index)/(cur->index-found->index)*(cur->height-found->height));
            return 0;
        }
        addElement(hashed, cur);
        int ** rock = calloc(5, sizeof(int *));
        for (int j = 0; j < 5 && rocks[i%5][j][0] != -1; j++) {
            rock[j] = malloc(2*sizeof(int));
            rock[j][0] = rocks[i%5][j][0]+height+3;
            rock[j][1] = rocks[i%5][j][1]+2;
        }
        while(true) {
            drop = !drop;
            if (drop) {
                bool stop = false;
                for (int j = 0; j < 5 && rock[j]; j++) {
                    rock[j][0]--;
                }
                for (int j = 0; j < 5 && rock[j]; j++) {
                    if (rock[j][0] < 0 || map[rock[j][0]][rock[j][1]]) {
                        stop = true;
                    }
                }
                if (stop) {
                    for (int j = 0; j < 5 && rock[j]; j++) {
                        rock[j][0]++;
                    }
                    break;
                }
            } else {
                for (int j = 0; j < 5 && rock[j]; j++) {
                    rock[j][1] += 2*push[w%(strlen(line)-1)]-1;
                }
                bool stop = false;
                for (int j = 0; j < 5 && rock[j]; j++) {
                    if (rock[j][1] < 0 || rock[j][1] >= 7 || map[rock[j][0]][rock[j][1]]) {
                        stop = true;
                    }
                }
                w++;
                if (stop) {
                    for (int j = 0; j < 5 && rock[j]; j++) {
                        rock[j][1] -= 2*push[(w-1)%(strlen(line)-1)]-1;
                    }
                }
            }
        }
        for (int j = 0; j < 5 && rock[j]; j++) {
            if (rock[j][0] >= height) {
                height = rock[j][0]+1;
            }
            map[rock[j][0]][rock[j][1]] = true;
        }
    }
    return 0;
}