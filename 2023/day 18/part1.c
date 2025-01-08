/* 
   Author: Itay Volk
   Date: 01/07/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 500

int trace(int x, int y, int width, int height, bool ** map) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return -1;
    }
    if (map[y][x]) {
        return 0;
    }
    map[y][x] = true;
    int count = 1;

    int temp = trace(x+1, y, width, height, map);
    if (temp == -1) {
        count = -1;
    } else {
        count += temp;
    }

    temp = trace(x-1, y, width, height, map);
    if (temp == -1) {
        count = -1;
    } else if (count != -1) {
        count += temp;
    }

    temp = trace(x, y+1, width, height, map);
    if (temp == -1) {
        count = -1;
    } else if (count != -1) {
        count += temp;
    }

    temp = trace(x, y-1, width, height, map);
    if (temp == -1 || count == -1) {
        return -1;
    }
    return count+temp;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    bool ** map = malloc(SIZE*sizeof(int*));
    for (int i = 0; i < SIZE; i++) {
        map[i] = calloc(SIZE, sizeof(bool));
    }

    int x = SIZE/2;
    int y = SIZE/2;
    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (x < 50)
            printf("%s%d:%d\n", line, x, y);
        char * ptr = line+2;
        int d = atoi(strtok_s(line+2, " ", &ptr));
        count += d;
        switch(line[0]) {
            case 'U':
                for (; d > 0; d--) {
                    map[--y][x] = true;
                }
                break;
            case 'D':
                for (; d > 0; d--) {
                    map[++y][x] = true;
                }
                break;
            case 'L':
                for (; d > 0; d--) {
                    map[y][--x] = true;
                }
                break;
            case 'R':
                for (; d > 0; d--) {
                    map[y][++x] = true;
                }
                break;
        }
    }
    printf("%d\n", count+trace(x, y-1, SIZE, SIZE, map));
    return 0;
}