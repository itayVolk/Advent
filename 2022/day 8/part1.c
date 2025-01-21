/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int **heights = malloc(100*sizeof(int *));
    int height = 0;
    int width;

    while(fgets(line, sizeof(line), fp)) {
        if (height == 0) {
            width = strlen(line)-1;
        }

        heights[height] = malloc(width*sizeof(int));
        for (int i = 0; i < width; i++) {
            heights[height][i] = line[i]-'0';
        }
        height++;
    }

    int count = 2*height + 2*width - 4;
    for (int i = 1; i < height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            bool visible = true;
            for (int k = i-1; k >= 0; k--) {
                if (heights[k][j] >= heights[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                count++;
                continue;;
            }
            visible = true;
            for (int k = i+1; k < height; k++) {
                if (heights[k][j] >= heights[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                count++;
                continue;
            }
            visible = true;
            for (int k = j-1; k >= 0; k--) {
                if (heights[i][k] >= heights[i][j]) {
                    visible = false;
                    break;
                }
            }
            if (visible) {
                count++;
                continue;
            }
            visible = true;
            for (int k = j+1; k < width; k++) {
                if (heights[i][k] >= heights[i][j]) {
                    visible = false;
                    break;
                }
            }
            count += visible;
        }
    }
    printf("%d\n", count);
    return 0;
}