/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 600

void move(int *tx, int *ty, int *hx, int *hy, int d) {
    if (d%2) {
        *hx += d-2;
    } else {
        *hy += d-1;
    }
    if (abs(*tx-*hx)+abs(*ty-*hy) == 3) {
        *tx += abs(*tx-*hx)/(*hx-*tx);
        *ty += abs(*ty-*hy)/(*hy-*ty);
    } else if (abs(*tx-*hx) == 2) {
        *tx += abs(*tx-*hx)/(*hx-*tx);
    } else if (abs(*ty-*hy) == 2) {
        *ty += abs(*ty-*hy)/(*hy-*ty);
    }
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool ** visited = malloc(SIZE*sizeof(bool *));
    for (int i = 0; i < SIZE; i++) {
        visited[i] = calloc(SIZE, sizeof(bool));
    }
    int tx = SIZE/2;
    int ty = SIZE/2;
    int hx = SIZE/2;
    int hy = SIZE/2;
    visited[ty][tx] = true;
    int count = 1;

    while (fgets(line, sizeof(line), fp)) {
        int d;
        switch(line[0]) {
            case 'U':
                d = 0;
                break;
            case 'D':
                d = 2;
                break;
            case 'L':
                d = 1;
                break;
            case 'R':
                d = 3;
        }
        for (int i = 0; i < atoi(line+2); i++) {
            move(&tx, &ty, &hx, &hy, d);
            if (!visited[ty][tx]) {
                visited[ty][tx] = true;
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}