/* 
   Author: Itay Volk
   Date: 12/14/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char * getString(int pos, int len, char string[])
{
    if (len == -1) {
        len = strlen(string)-pos;
    }
    char * substring = calloc(len+1, sizeof(char));
    int i = 0;
    while (i < len) {
        substring[i] = string[pos + i];
        i++;
    }
    return substring;
}

bool move(int x, int y, int dx, int dy, int **map) {
    if (map[y][x] == 1) {
        return false;
    }
    if (map[y][x] == 0) {
        return true;
    }
    bool next = move(x+dx, y+dy, dx, dy, map);
    if (next) {
        map[y+dy][x+dx] = -1;
        map[y][x] = 0;
    }
    return next;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int y = 0;
    int x = 0;

    int ** arr = malloc(200*sizeof(int*));
    int height = 0;
    int width = 0;

    while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
        if (width == 0) {
            width = strlen(line);
        }
        arr[height] = calloc(width, sizeof(int));
        for (int i = 0; i < width; i++) {
            if (line[i] == '#') {
                arr[height][i] = 1;
            } else if (line[i] == '@') {
                y = height;
                x = i;
            }if (line[i] == 'O') {
                arr[height][i] = -1;
            } 
        }
        height++;
    }
    width--;

    char * buffer = calloc(10000, sizeof(char));
    while(fgets(line, sizeof(line), fp) != NULL) {
        strcat(buffer, getString(0, -1, line));
    }

    for (int i = 0; i < strlen(buffer); i++) {
        int dx = 0;
        int dy = 0;
        switch (buffer[i]) {
            case '>':
                dx = 1;
            break;
            case '<':
                dx = -1;
            break;
            case '^':
                dy = -1;
            break;
            case 'v':
                dy = 1;
            break;
        }
        if (move(x+dx, y+dy, dx, dy, arr)) {
            x += dx;
            y += dy;
        }
    }

    int sum = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] == -1) {
                sum += i*100 + j;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}