/* 
   Author: Itay Volk
   Date: 12/05/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool loops (int ** data, int height, int width, int x, int y, bool initial) {
    int ** arr;
    if (initial) {
        arr = data;
    } else {
        arr = malloc(height*sizeof(int*));
        for (int i = 0; i < height; i++) {
            arr[i] = calloc(width, sizeof(int));
            for (int j = 0; j < width; j++) {
                if (data[i][j] != 0) {
                    arr[i][j] = data[i][j];
                }
            }
        }
    }
    int dir = 0;
    while(y >= 0 && y < height && x >= 0 && x < width) {
        if (dir%2 == 0) {
            y += dir-1;
            if (y >= 0 && y < height) {
                if (arr[y][x] == 1) {
                    y -= dir-1;
                    dir++;
                } else if (initial) {
                    arr[y][x] = -1;
                } else if (arr[y][x] == 0) {
                    arr[y][x] = -3*dir/2-1;
                } else if (((-1*arr[y][x])&(3*dir/2+1)) > 0) {
                    return true;
                } else {
                    arr[y][x] += -3*dir/2-1;
                }
            }
        } else {
            x -= dir-2;
            if (x >= 0 && x < width) {
                if (arr[y][x] == 1) {
                    x += dir-2;
                    dir = (dir+1)%4;
                } else if (initial) {
                    arr[y][x] = -1;
                } else if (arr[y][x] == 0) {
                    arr[y][x] = -3*dir+1;
                } else if (((-1*arr[y][x])&(3*dir-1)) > 0) {
                    return true;
                } else {
                    arr[y][x] += -3*dir+1;
                }
            }
        }
    }
    return false;
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
                arr[height][i] = 1;
            } else if (line[i] == '^') {
                arr[height][i] = -1;
                y = height;
                x = i;
            }
        }
        height++;
    }

    int ** path = malloc(height*sizeof(int*));
    for (int i = 0; i < height; i++) {
        path[i] = calloc(width, sizeof(int));
        for (int j = 0; j < width; j++) {
            if (arr[i][j] != 0) {
                path[i][j] = arr[i][j];
            }
        }
    }
    loops(path, height, width, x, y, true);
    
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((i != y || j != x) && path[i][j] == -1) {
                arr[i][j] = 1;
                if (loops(arr, height, width, x, y, false)) {
                    count++;
                }
                arr[i][j] = 0;
            }
        }
    }

    printf("%d\n", count);
    return 0;
}