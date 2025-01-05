/* 
   Author: Itay Volk
   Date: 01/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

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

    long long sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == 1) {
                sum += height-i;
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}