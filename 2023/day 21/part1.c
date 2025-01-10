/* 
   Author: Itay Volk
   Date: 01/09/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STEPS 64

int trace(int x, int y, int width, int height, bool ** map, bool *** visited, int step) {
    if (x < 0 || x >= width || y < 0 || y >= width || map[y][x] || visited[step][y][x]) {
        return 0;
    }
    visited[step][y][x] = true;
    if (step == 0) {
        return 1;
    }
    step--;
    return trace(x+1, y, width, height, map, visited, step) + trace(x-1, y, width, height, map, visited, step) + trace(x, y+1, width, height, map, visited, step) + trace(x, y-1, width, height, map, visited, step);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool ** map = malloc(150*sizeof(bool*));
    int height = 0;
    int width;
    int x = 0;
    int y = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        map[height] = calloc(width, sizeof(bool));
        for (int i = 0; i < width; i++) {
            map[height][i] = line[i] == '#';
            if (line[i] == 'S') {
                y = height;
                x = i;
            }
        }
        height++;
    }

    bool *** visited = malloc((STEPS+1)*sizeof(bool **));
    for (int i = 0; i < STEPS+1; i++) {
        visited[i] = malloc(height*sizeof(bool *));
        for (int j = 0; j < height; j++) {
            visited[i][j] = calloc(width, sizeof(bool));
        }
    }
    printf("%d\n", trace(x, y, width, height, map, visited, STEPS));
    return 0;
}