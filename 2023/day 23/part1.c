/* 
   Author: Itay Volk
   Date: 01/10/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef enum tile {PATH, FOREST, NORTH, EAST, SOUTH, WEST} TILE;

int moveX(int x, int d) {
    if (d%2 == 0) {
        return x;
    }
    return x - d + 4;
}

int moveY(int y, int d) {
    if (d%2 == 1) {
        return y;
    }
    return y + d - 3;
}

bool ** paste(bool ** visited, int width, int height) {
    bool ** copy = malloc(height*sizeof(bool *));
    for (int i = 0; i < height; i++) {
        copy[i] = malloc(width*sizeof(bool));
        for (int j = 0 ; j < width; j++) {
            copy[i][j] = visited[i][j];
        }
    }
    return copy;
}

int buildGraph(TILE ** map, int x, int y, int width, int height, bool ** visited) {
    if (x < 0 || x >= width || y < 0 || y >= height || visited[y][x]) {
        return -1;
    }
    if (x == width-2 && y == height-2) {
        return 1;
    }
    visited[y][x] = true;
    switch (map[y][x]) {
        case PATH:
            int count = -1;
            for (int d = NORTH; d <= WEST; d++) {
                int temp = buildGraph(map, moveX(x, d), moveY(y, d), width, height, paste(visited, width, height));
                if (temp != -1 && temp+1 > count) {
                    count = temp+1;
                }
            }
            return count;
        case FOREST:
            return -1;
        case NORTH:
        case EAST:
        case SOUTH:
        case WEST:
            int temp = buildGraph(map, moveX(x, map[y][x]), moveY(y, map[y][x]), width, height, visited);
            return temp == -1 ? -1 : temp+1;
    }
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    TILE ** map = malloc(150*sizeof(TILE *));
    int height = 0;
    int width;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (height == 0) {
            width = strlen(line)-1;
        }
        map[height] = malloc(width*sizeof(TILE));
        for (int i = 0; i < width; i++) {
            switch (line[i]) {
                case '.':
                    map[height][i] = PATH;
                    break;
                case '#':
                    map[height][i] = FOREST;
                    break;
                case '^':
                    map[height][i] = NORTH;
                    break;
                case '>':
                    map[height][i] = EAST;
                    break;
                case 'v':
                    map[height][i] = SOUTH;
                    break;
                case '<':
                    map[height][i] = WEST;
                    break;
            }
        }
        height++;
    }

    map[0][1] = FOREST;
    bool ** visited = malloc(height*sizeof(bool *));
    for (int i = 0; i < height; i++) {
        visited[i] = calloc(width, sizeof(bool));
    }
    printf("%d\n", buildGraph(map, 1, 1, width, height, visited)+1);
    return 0;
}