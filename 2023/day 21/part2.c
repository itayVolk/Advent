/* 
   Author: Itay Volk
   Date: 01/09/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int trace(int x, int y, int width, int height, bool ** map, bool *** visited, int step) {
    if (map[y%height][x%width] || visited[step][y][x]) { 
        return 0;
    }
    visited[step][y][x] = true;
    if (step == 0) {
        return 1;
    }
    step--;
    return trace(x+1, y, width, height, map, visited, step) + trace(x-1, y, width, height, map, visited, step) + trace(x, y+1, width, height, map, visited, step) + trace(x, y-1, width, height, map, visited, step);
}

#define NUM 3

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
    bool **** visited = malloc(NUM*sizeof(bool ***));
    int * values = malloc(NUM*sizeof(int));
    for (int k = 0; k < NUM; k++) {
        visited[k] = malloc(height*(k+1.5)*sizeof(bool **));
        for (int i = 0; i < height*(k+1.5); i++) {
            visited[k][i] = malloc((NUM*2-1)*height*sizeof(bool *));
            for (int j = 0; j < (NUM*2-1)*height; j++) {
                visited[k][i][j] = calloc((NUM*2-1)*width, sizeof(bool));
            }
        }
        values[k] = trace(x+width*(NUM-1), y+height*(NUM-1), width, height, map, visited[k], height*(k+0.5));
    }
    long long num = 26501365.0/height;
    long long a = (values[2] - 2*values[1] + values[0])/2;
    long long b = values[1] - a - values[0];
    long long c = values[0];
    printf("%lld\n", a*num*num + b*num + c);
    return 0;
}