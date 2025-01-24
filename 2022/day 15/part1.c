/* 
   Author: Itay Volk
   Date: 01/23/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6000000

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int * map = calloc(SIZE, sizeof(int));
    while(fgets(line, sizeof(line), fp)) {
        int sx = atoi(strtok(line+12, ", y=")) + SIZE/5;
        int sy = atoi(strtok(NULL, ", y=")) + SIZE/5;
        int ex = atoi(strtok(NULL, ": closest beacon is at x=")) + SIZE/5;
        int ey = atoi(strtok(NULL, ", y=")) + SIZE/5;
        if (ey == 2000000 + SIZE/5) {
            map[ex] = -1;
        }
        int d = abs(ex-sx) + abs(ey-sy);
        int r = 2000000 + SIZE/5 - sy;
        if (d >= abs(r)) {
            for (int i = -(d-abs(r)); i <= d-abs(r); i++) {
                if (!map[sx+i]) {
                    map[sx+i] = 1;
                }
            }
        }
    }

    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        if (map[i] == 1) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}