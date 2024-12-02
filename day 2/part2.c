/* 
   Author: Itay Volk
   Date: 12/01/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

bool isSafe(int * arr, int l) {
    int dir = 0;
    for (int i = 1; i < l; i++) {
        int dif = arr[i-1]-arr[i];
        if(dif == 0) {
            return false;
        }
        if (dir == 0) {
            dir = dif/abs(dif);
        } else if (dir != dif/abs(dif)) {
            return false;
        }
        if (abs(dif) > 3) {
            return false;
        }
    }
    return true;
}

int main() {
    int *arr = calloc(10, sizeof(int));
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    int count = 0;
    int loc = 1;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int *arr = calloc(10, sizeof(int));
        char * token = strtok(line, " ");
        int l = 0;
        while (token != NULL) {
            arr[l++] = atoi(token);
            token = strtok(NULL, " ");
        }
        if (isSafe(arr, l)) {
            count++;
        }  else {
            for (int i = 0; i < l; i++) {
                int * temp = calloc(l-1, sizeof(int));
                for (int j = 0; j < i; j++) {
                    temp[j] = arr[j];
                }
                for (int j = i+1; j < l; j++) {
                    temp[j-1] = arr[j];
                }
                if(isSafe(temp, l-1)) {
                    count++;
                    break;
                }
            }
        }
        loc++;
    }
    printf("%d\n", count);
    return 0;
}