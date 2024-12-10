/* 
   Author: Itay Volk
   Date: 12/09/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int trail(int x, int y, int width, int height, int ** map) {
    if (map[y][x] == 9) {
        return 1;
    }
    int count = 0;;
    if (x > 0 && map[y][x-1] - map[y][x] == 1) {
        count += trail(x-1, y, width, height, map);
    }
    if (x < width-1 && map[y][x+1] - map[y][x] == 1) {
        count += trail(x+1, y, width, height, map);
    }
    if (y > 0 && map[y-1][x] - map[y][x] == 1) {
        count += trail(x, y-1, width, height, map);
    }
    if (y < height-1 && map[y+1][x] - map[y][x] == 1) {
        count += trail(x, y+1, width, height, map);
    }
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int y = 0;
    int x = 0;

    int ** arr = malloc(60*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line)-1;
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            arr[height][i] = line[i]-'0';
        }
        height++;
    }

    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] == 0) {
                int count = trail(j, i, width, height, arr);
                sum += count;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}