/* 
   Author: Itay Volk
   Date: 12/01/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    int *arr = calloc(10, sizeof(int));
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int *arr = calloc(10, sizeof(int));
        char * token = strtok(line, " ");
        int l = 0;
        while (token != NULL) {
            arr[l++] = atoi(token);
            token = strtok(NULL, " ");
        }
        int dir = 0;
        bool safe = true;
        for (int i = 1; i < l; i++) {
            int dif = arr[i-1]-arr[i];
            if(dif == 0) {
                safe = false;
                break;
            }
            if (dir == 0) {
                dir = dif/abs(dif);
            } else if (dir != dif/abs(dif)) {
                safe = false;
                break;
            }
            if (abs(dif) > 3) {
                safe = false;
                break;
            }
        }
        if (safe) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}