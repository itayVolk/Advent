/* 
   Author: Itay Volk
   Date: 12/27/2024
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char * getString(int pos, int len, char string[]) {
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

bool include(char ** search, int width, int height, int x, int y, int length) {
    if (x-1 >= 0) {
        if (search[y][x-1] != '.') {
            // printf("a");
            return true;
        }
        if (y-1 >= 0 && search[y-1][x-1] != '.') {
            // printf("b");
            return true;
        }
        if (y+1 < height && search[y+1][x-1] != '.') {
            // printf("c");
            return true;
        }
    }
    if (x+length < width) {
        if (search[y][x+length] != '.') {
            // printf("d");
            return true;
        }
        if (y-1 >= 0 && search[y-1][x+length] != '.') {
            // printf("e");
            return true;
        }
        if (y+1 < height && search[y+1][x+length] != '.') {
            // printf("f");
            return true;
        }
    }
    for (int i = 0; i < length; i++) {
        if (y-1 >= 0 && search[y-1][x+i] != '.') {
            // printf("g");
            return true;
        }
        if (y+1 < height && search[y+1][x+i] != '.') {
            // printf("h");
            return true;
        }
    }
    return false;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char **search = malloc(256*sizeof(char*));
    int height = 0;
    search[height] = calloc(256, sizeof(char));
    while(fgets(search[height], 256*sizeof(char), fp) != NULL) {
        search[++height] = calloc(256, sizeof(char));
    }
    
    int sum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < strlen(search[y])-1; x++) {
            if (isdigit(search[y][x])) {
                int start = x;
                while (isdigit(search[y][x])) {
                    x++;
                }
                x--;
                if (include(search, strlen(search[y])-1, height, start, y, x-start+1)) {
                    // printf("included%d-%d|%s\n", start, x, getString(start, x-start+1, search[y]));
                    sum += atoi(getString(start, x-start+1, search[y]));
                }
                x++;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}