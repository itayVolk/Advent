/* 
   Author: Itay Volk
   Date: 12/03/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool checkCell(char ** search, int length, int x, int y) {
    if (search[y][x] != 'A') {
        return false;
    }
    return (search[y-1][x-1] + search[y+1][x+1]) == 160 && (search[y-1][x+1] + search[y+1][x-1]) == 160;
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
    for (int y = 1; y < length-1; y++) {
        for (int x = 1; x < strlen(search[y])-1; x++) {
            count += checkCell(search, length, x, y);
        }
    }

    printf("%d\n", count);
    return 0;
}