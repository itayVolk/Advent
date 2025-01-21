/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 600

void move(int x[10], int y[10], int d) {
    if (d%2) {
        x[0] += d-2;
    } else {
        y[0] += d-1;
    }
    
    for (int i = 1; i < 10; i++) {
        if (abs(x[i]-x[i-1])+abs(y[i]-y[i-1]) >= 3) {
            x[i] += abs(x[i]-x[i-1])/(x[i-1]-x[i]);
            y[i] += abs(y[i]-y[i-1])/(y[i-1]-y[i]);
        } else if (abs(x[i]-x[i-1]) == 2) {
            x[i] += abs(x[i]-x[i-1])/(x[i-1]-x[i]);
        } else if (abs(y[i]-y[i-1]) == 2) {
            y[i] += abs(y[i]-y[i-1])/(y[i-1]-y[i]);
        }
    }
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool ** visited = malloc(SIZE*sizeof(bool *));
    for (int i = 0; i < SIZE; i++) {
        visited[i] = calloc(SIZE, sizeof(bool));
    }
    int x[10];
    int y[10];
    for (int i = 0; i < 10; i++) {
        x[i] = SIZE/2;
        y[i] = SIZE/2;
    }
    visited[y[9]][x[9]] = true;
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
            move(x, y, d);
            if (!visited[y[9]][x[9]]) {
                visited[y[9]][x[9]] = true;
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}