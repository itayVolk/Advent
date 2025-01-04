/* 
   Author: Itay Volk
   Date: 01/03/2025
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

typedef struct cache {
    int * data;
    int size;
    int blocks;
    int loc;
    long long value;
} CACHE;

static unsigned hash (CACHE * a) {
    unsigned hash = 0;
    for (int i = 0; i < a->size; i++) {
        hash *= 2;
        hash += !!a->data[i];
    } 
    return hash;
}

static int compare(CACHE * a, CACHE * b) {
    if (a->size != b->size || a->loc != b->loc || a->blocks != b->blocks) {
        return 1;
    }
    for (int i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) {
            return 1;
        }
    }
    return 0;
}

long long calc (int * status, int count, int * blocks, int numBlocks, int loc, SET * cache) {
    if (count == 0) {
        return numBlocks == 0 || numBlocks == 1 && blocks[0] == loc;
    }
    CACHE * search = malloc(sizeof(CACHE));
    search->data = status;
    search->size = count;
    search->blocks = numBlocks;
    search->loc = loc;
    CACHE * found = findElement(cache, search);
    if (found != NULL) {
        return found->value;
    }

    long long out = 0;
    switch(status[0]) {
        case -1:
            if (numBlocks > 0 && loc < blocks[0]) {
                out += calc(status+1, count-1, blocks, numBlocks, loc+1, cache);
            }
            if (loc > 0) {
                if (blocks[0] == loc) {
                    out += calc(status+1, count-1, blocks+1, numBlocks-1, 0, cache);
                }
            } else {
                out += calc(status+1, count-1, blocks, numBlocks, 0, cache);
            }
            break;
        case 0:
            if (loc > 0) {
                if (blocks[0] == loc) {
                    out = calc(status+1, count-1, blocks+1, numBlocks-1, 0, cache);
                }
            }else {
                out = calc(status+1, count-1, blocks, numBlocks, 0, cache);
            }
            break;
        case 1:
            if (numBlocks > 0 && loc < blocks[0]) {
                out = calc(status+1, count-1, blocks, numBlocks, loc+1, cache);
            } 
    }
    search->value = out;
    addElement(cache, search);
    return out;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    long long total = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        int * status = calloc(125, sizeof(int));
        int count = 0;
        while (line[count] != ' ') {
            status[count] = line[count]=='#';
            if (line[count] == '?') {
                status[count] = -1;
            }
            count++;
        }

        status[count] = -1;
        status[count*2+1] = -1;
        status[count*3+2] = -1;
        status[count*4+3] = -1;
        for (int i = 0; i < count; i++) {
            status[i+count+1] = status[i];
            status[i+count*2+2] = status[i];
            status[i+count*3+3] = status[i];
            status[i+count*4+4] = status[i];
        }
        count *= 5;
        count += 4;

        char * ptr = line;
        char * tok = strtok_s(line+count/5+1, ",", &ptr);
        int * blocks = calloc(125, sizeof(int));
        int numBlocks = 0;
        while (tok != NULL) {
            blocks[numBlocks++] = atoi(tok);
            tok = strtok_s(NULL, ",", &ptr);
        }
        for (int i = 0; i < numBlocks; i++) {
            blocks[i+numBlocks] = blocks[i];
            blocks[i+numBlocks*2] = blocks[i];
            blocks[i+numBlocks*3] = blocks[i];
            blocks[i+numBlocks*4] = blocks[i];
        }
        numBlocks *= 5;
        total += calc(status, count, blocks, numBlocks, 0, createSet(1000000, compare, hash));
    }
    printf("%lld\n", total);
    return 0;
}