/* 
   Author: Itay Volk
   Date: 01/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "table.h"

typedef struct dict {
    int ** map;
    int width;
    int height;
    int n;
} DICT;

static unsigned hash(DICT * a) {
    int hash = 0;
    hash = 0;
    for (int i = 0; i < a->height; i++) {
        for (int j = 0; j < a->width; j++) {
            if (a->map[i][j] == 1) {
                hash += a->height-i;
            }
        }
    }
    return hash;
}

static int compare(DICT * a, DICT * b) {
    if (a->width != b->width || a->height != b->height) {
        return 1;
    }
    for (int i = 0; i < a->height; i++) {
        for (int j = 0; j < a->width; j++) {
            if (a->map[i][j] != b->map[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}

#define MAX 1000000000

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    int ** map = malloc(150*sizeof(int *));
    int height = 0;
    int width;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        map[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            map[height][i] = line[i]=='O';
            if (line[i] == '#') {
                map[height][i] = 2;
            }
        }
        height++;
    }
    
    SET * cycles = createSet(MAX, compare, hash);

    for (int n = 0; n < MAX; n++) {
        for (int i = 0; i < width; i++) {
            for (int j = 1; j < height; j++) {
                if (map[j][i] == 1 && map[j-1][i] == 0) {
                    map[j][i] = 0;
                    map[--j][i] = 1;
                    if (j > 0) {
                        j--;
                    }
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = 1; j < width; j++) {
                if (map[i][j] == 1 && map[i][j-1] == 0) {
                    map[i][j] = 0;
                    map[i][--j] = 1;
                    if (j > 0) {
                        j--;
                    }
                }
            }
        }
        for (int i = 0; i < width; i++) {
            for (int j = height-2; j >= 0; j--) {
                if (map[j][i] == 1 && map[j+1][i] == 0) {
                    map[j][i] = 0;
                    map[++j][i] = 1;
                    if (j < height-1) {
                        j++;
                    }
                }
            }
        }
        for (int i = 0; i < height; i++) {
            for (int j = width-2; j >= 0; j--) {
                if (map[i][j] == 1 && map[i][j+1] == 0) {
                    map[i][j] = 0;
                    map[i][++j] = 1;
                    if (j < width-1) {
                        j++;
                    }
                }
            }
        }
        
        DICT * search = malloc(sizeof(DICT));
        search->width = width;
        search->height = height;
        search->map = malloc(height*sizeof(int*));
        for (int i = 0; i < height; i++) {
            search->map[i] = malloc(width*sizeof(int));
            for (int j = 0; j < width; j++) {
                search->map[i][j] = map[i][j];
            }
        }

        DICT * found = findElement(cycles, search);
        if (found != NULL) {
            int pos = found->n+(MAX-found->n)%(n-found->n)-1;
            DICT ** elements = getElements(cycles);
            for (int i = 0; i < numElements(cycles); i++) {
                if (elements[i]->n == pos) {
                    printf("%u\n", hash(elements[i]));
                    break;
                }
            }
            break;
        }
        search->n = n;
        addElement(cycles, search);
    }
    return 0;
}