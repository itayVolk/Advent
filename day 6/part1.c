/* 
   Author: Itay Volk
   Date: 12/05/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
                arr[height][i] = 1;
            } else if (line[i] == '^') {
                arr[height][i] = -1;
                y = height;
                x = i;
            }
        }
        height++;
    }

    int count = 1;
    int dir = 0;
    while(y >= 0 && y < height && x >= 0 && x < width) {
        if (dir%2 == 0) {
            y += dir-1;
            if (y >= 0 && y < height) {
                if (arr[y][x] == 1) {
                    y -= dir-1;
                    dir++;
                } else if (arr[y][x] == 0) {
                    arr[y][x] = -1;
                    count++;
                }
            }
        } else {
            x -= dir-2;
            if (x >= 0 && x < width) {
                if (arr[y][x] == 1) {
                    x += dir-2;
                    dir = (dir+1)%4;
                } else if (arr[y][x] == 0) {
                    arr[y][x] = -1;
                    count++;
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}