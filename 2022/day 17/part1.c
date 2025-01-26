/* 
   Author: Itay Volk
   Date: 01/25/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[12000];
    fgets(line, sizeof(line), fp);
    bool * push = malloc((strlen(line)-1)*sizeof(bool));
    for (int i = 0; i < strlen(line)-1; i++) {
        push[i] = line[i]=='>';
    }

    bool ** map = malloc(5000*sizeof(bool *));
    for (int i = 0; i < 5000; i++) {
        map[i] = calloc(7, sizeof(bool));
    }

    int rocks[5][5][2] = {{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, -1}},
                        {{0, 1}, {1, 0}, {1, 1}, {1, 2}, {2, 1}},
                        {{2, 2}, {1, 2}, {0, 0}, {0, 1}, {0, 2}},
                        {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {-1, -1}},
                        {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {-1, -1}}};

    int height = 0;
    int w = 0;
    bool drop = true;
    for (int i = 0; i < 2022; i++) {
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
    printf("%d\n", height);
    return 0;
}