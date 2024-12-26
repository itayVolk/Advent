/* 
   Author: Itay Volk
   Date: 12/03/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool checkDir(char ** search, int length, int x, int y, int dx, int dy) {
    char *xmas = "XMAS";
    while(y >= 0 && y < length && x >= 0 && x < strlen(search[y]) && strlen(xmas) > 0 && search[y][x] == xmas[0]) {
        xmas++;
        x += dx;
        y += dy;
    }
    return strlen(xmas) == 0;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char **search = malloc(256*sizeof(char*));
    int length = 0;
    search[length] = calloc(256, sizeof(char));
    while(fgets(search[length], 256*sizeof(char), fp) != NULL) {
        search[++length] = calloc(256, sizeof(char));
    }
    
    int count = 0;
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < strlen(search[y]); x++) {
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    count += checkDir(search, length, x, y, dx, dy);
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}