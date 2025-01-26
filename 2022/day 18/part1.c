/* 
   Author: Itay Volk
   Date: 01/25/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 20

int edgeCount(int x, int y, int z, bool *** scan, bool *** visited) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || z < 0 || z >= SIZE || !scan[x][y][z]) {
        return 1;
    }
    if (visited[x][y][z]) {
        return 0;
    }
    visited[x][y][z] = true;
    int count = edgeCount(x+1, y, z, scan, visited);
    count += edgeCount(x-1, y, z, scan, visited);
    count += edgeCount(x, y+1, z, scan, visited);
    count += edgeCount(x, y-1, z, scan, visited);
    count += edgeCount(x, y, z+1, scan, visited);
    count += edgeCount(x, y, z-1, scan, visited);
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool *** scan = malloc(SIZE*sizeof(bool **));
    bool *** visited = malloc(SIZE*sizeof(bool **));
    for (int i = 0; i < SIZE; i++) {
        scan[i] = malloc(SIZE*sizeof(bool *));
        visited[i] = malloc(SIZE*sizeof(bool *));
        for (int j = 0; j < SIZE; j++) {
            scan[i][j] = calloc(SIZE, sizeof(bool));
            visited[i][j] = calloc(SIZE, sizeof(bool));
        }
    }
    while(fgets(line, sizeof(line), fp)) {
        scan[atoi(strtok(line, ","))][atoi(strtok(NULL, ","))][atoi(strtok(NULL, ","))] = true;
    }

    int total = 0;
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < SIZE; z++) {
                if (scan[x][y][z] && !visited[x][y][z]) {
                    total += edgeCount(x, y, z, scan, visited);
                }
            }
        }
    }
    printf("%d\n", total);
    return 0;
}