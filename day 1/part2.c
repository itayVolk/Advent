/* 
   Author: Itay Volk
   Date: 11/30/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define NUM 1000

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int main() {
    int *list_a = calloc(NUM, sizeof(int));
    int *list_b = calloc(NUM, sizeof(int));
    FILE * fp = fopen("data.txt", "r");
    char line[256];
    for (int i = 0; i < NUM; i++) {
        fgets(line, sizeof(line), fp);
        list_a[i] = atoi(strtok(line, " "));
        list_b[i] = atoi(strtok(NULL, " "));
    }
    int siml = 0;
    for (int i = 0; i < NUM; i++) {
        int count = 0;
        for (int j = 0; j < NUM; j++) {
            if (list_a[i] == list_b[j]) {
                count++;
            }
        }
        siml += list_a[i]*count;
    }
    printf("%d\n", siml);
    return 0;
}