/* 
   Author: Itay Volk
   Date: 12/11/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int trace(int x, int y, int width, int height, bool **counted, int ** map, int  * edges) {
    if (counted[y][x]) {
        return 0;
    }
    counted[y][x] = true;
    int count = 1;
    if (x > 0) {
        if (map[y][x-1] == map[y][x]) {
            count += trace(x-1, y, width, height, counted, map, edges);
        } else {
            (*edges)++;
        }
    } else {
        (*edges)++;
    }
    if (x < width-1) {
        if (map[y][x+1] == map[y][x]) {
            count += trace(x+1, y, width, height, counted, map, edges);
        } else {
            (*edges)++;
        }
    } else {
        (*edges)++;
    }
    if (y > 0) {
        if (map[y-1][x] == map[y][x]) {
            count += trace(x, y-1, width, height, counted, map, edges);
        } else {
            (*edges)++;
        }
    } else {
        (*edges)++;
    }
    if (y < height-1) {
        if (map[y+1][x] == map[y][x]) {
            count += trace(x, y+1, width, height, counted, map, edges);
        } else {
            (*edges)++;
        }
    } else {
        (*edges)++;
    }
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int y = 0;
    int x = 0;

    int ** arr = malloc(150*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (width == 0) {
            width = strlen(line)-1;
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            arr[height][i] = line[i]-'A';
        }
        height++;
    }

    bool ** counted = malloc(height*sizeof(bool*));
    for (int i = 0; i < height; i++) {
        counted[i] = calloc(width, sizeof(bool));
    }

    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!counted[i][j]) {
                int edges = 0;
                int area = trace(j, i, width, height, counted, arr, &edges);
                sum += area * edges;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}