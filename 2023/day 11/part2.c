/* 
   Author: Itay Volk
   Date: 01/02/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    int ** galaxies = malloc(500*sizeof(int*));
    int numGal = 0;
    bool ** space = malloc(150*sizeof(bool *));
    int width;
    int height = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        space[height] = calloc(width, sizeof(bool));
        for (int i = 0; i < width; i++) {
            if (line[i] == '#') {
                space[height][i] = true;
                galaxies[numGal] = calloc(2, sizeof(int));
                galaxies[numGal][0] = height;
                galaxies[numGal][1] = i;
                numGal++;
            }
        }
        height++;
    }

    int ** expanded = malloc(numGal*sizeof(int *));
    for (int i = 0; i < numGal; i++) {
        expanded[i] = calloc(2, sizeof(int));
    }

    for (int i = 0; i < height; i++) {
        bool expand = true;
        for (int j = 0; j < width; j++) {
            if (space[i][j]) {
                expand = false;
                break;
            }
        }
        if (expand) {
            for (int j = 0; j < numGal; j++) {
                if (galaxies[j][0] > i) {
                    expanded[j][0]++;
                }
            }
        }
    }

    for (int i = 0; i < width; i++) {
        bool expand = true;
        for (int j = 0; j < height; j++) {
            if (space[j][i]) {
                expand = false;
                break;
            }
        }
        if (expand) {
            for (int j = 0; j < numGal; j++) {
                if (galaxies[j][1] > i) {
                    expanded[j][1]++;
                }
            }
        }
    }

    long move = 0;
    long expand = 0;
    for (int i = 0; i < numGal; i++) {
        for (int j = i+1; j < numGal; j++) {
            expand += abs(expanded[i][0]-expanded[j][0]) + abs(expanded[i][1]-expanded[j][1]);
            move += abs(galaxies[i][0]-galaxies[j][0]) + abs(galaxies[i][1]-galaxies[j][1]);
        }
    }
    printf("%lld\n", (long long)expand*999999+move);
    return 0;
}