/* 
   Author: Itay Volk
   Date: 01/10/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define SX 10
#define SY 10
#define SZ 400

bool blockCheck(int * blocked, int num, int check) {
    for (int i = 0; i < num; i++) {
        if (blocked[i] == check) {
            return true;
        }
    }
    return false;
}

int fallCheck(int *** stack, int num) {
    bool * dropped = calloc(num-1, sizeof(bool));
    int drop = 0;
    for (int z = 1; z < SZ; z++) {
        int * blocked = calloc(SY*SX, sizeof(int));
        int numBlocked = 0;
        for (int y = 0; y < SY; y++) {
            for (int x = 0; x < SX; x++) {
                if (stack[z-1][y][x] != 0 && stack[z][y][x] != 0 && !blockCheck(blocked, numBlocked, stack[z][y][x])) {
                    blocked[numBlocked++] = stack[z][y][x];
                }
            }
        }

        bool moved = false;
        for (int y = 0; y < SY; y++) {
            for (int x = 0; x < SX; x++) {
                if (stack[z-1][y][x] == 0 && stack[z][y][x] != 0 && !blockCheck(blocked, numBlocked, stack[z][y][x])) {
                    stack[z-1][y][x] = stack[z][y][x];
                    if (!dropped[stack[z][y][x]-1]) {
                        drop++;
                        dropped[stack[z][y][x]-1] = true;
                    }
                    stack[z][y][x] = 0;
                    moved = true;
                }
            }
        }
        if (moved) {
            z--;
            if (z > 0) {
                z--;
            }
        }
    }
    return drop;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int *** stack = malloc(SZ*sizeof(int **));
    for (int i = 0; i < SZ; i++) {
        stack[i] = malloc(SY*sizeof(int *));
        for (int j = 0; j < SY; j++) {
            stack[i][j] = calloc(SX, sizeof(int));
        }
    }
    int num = 1;

    while (fgets(line, sizeof(line), fp) != NULL) {
        int sx = atoi(strtok(line, ",~"));
        int sy = atoi(strtok(NULL, ",~"));
        int sz = atoi(strtok(NULL, ",~"))-1;
        int ex = atoi(strtok(NULL, ",~"));
        int ey = atoi(strtok(NULL, ",~"));
        int ez = atoi(strtok(NULL, ",~"))-1;
        for (int x = sx; x <= ex; x++) {
            for (int y = sy; y <= ey; y++) {
                for (int z = sz; z <= ez; z++) {
                    stack[z][y][x] = num;
                }
            }
        }
        num++;
    }

    fallCheck(stack, num);

    bool ** support = malloc((num-1)*sizeof(bool *));
    for (int i = 0; i < num-1; i++) {
        support[i] = calloc(num-1, sizeof(bool));
    }

    for (int z = 1; z < SZ; z++) {
        for (int y = 0; y < SY; y++) {
            for (int x = 0; x < SX; x++) {
                if (stack[z-1][y][x] != 0 && stack[z][y][x] != 0 && stack[z-1][y][x] != stack[z][y][x]) {
                    support[stack[z][y][x]-1][stack[z-1][y][x]-1] = true;
                }
            }
        }
    }

    long long count = 0;
    for (int i = 0; i < num-1; i++) {
        int *** copy = malloc(SZ*sizeof(int **));
        for (int z = 0; z < SZ; z++) {
            copy[z] = malloc(SY*sizeof(int *));
            for (int y = 0; y < SY; y++) {
                copy[z][y] = calloc(SX, sizeof(int));
                for (int x = 0; x < SX; x++) {
                    copy[z][y][x] = stack[z][y][x];
                    if (copy[z][y][x] == i+1) {
                        copy[z][y][x] = 0;
                    }
                }
            }
        }
        count += fallCheck(copy, num);
    }
    // printf("%d\n", num);
    printf("%lld\n", count);
    return 0;
}