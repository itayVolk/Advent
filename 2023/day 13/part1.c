/* 
   Author: Itay Volk
   Date: 01/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    long long sum = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        bool ** grid = malloc(30*sizeof(bool *));
        int height = 0;
        int width;
        do {
            if (height == 0) {
                width = strlen(line)-1;
            }
            grid[height] = calloc(width, sizeof(bool));
            for (int i = 0; i < width; i++) {
                grid[height][i] = line[i]=='#';
            }
            height++;
        } while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n"));

        for (int i = 1; i < width; i++) {
            int left = i-1;
            int right = i;
            bool pass = true;
            while (left >= 0 && right < width) {
                for (int j = 0; j < height; j++) {
                    if (grid[j][left] != grid[j][right]) {
                        pass = false;
                    }
                }
                if (!pass) {
                    break;
                }
                left--;
                right++;
            }
            if (pass) {
                sum += i;
            }
        }

        for (int i = 1; i < height; i++) {
            int left = i-1;
            int right = i;
            bool pass = true;
            while (left >= 0 && right < height) {
                for (int j = 0; j < width; j++) {
                    if (grid[left][j] != grid[right][j]) {
                        pass = false;
                    }
                }
                if (!pass) {
                    break;
                }
                left--;
                right++;
            }
            if (pass) {
                sum += 100*i;
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}