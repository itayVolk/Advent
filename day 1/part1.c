/* 
   Author: Itay Volk
   Date: 11/30/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    qsort(list_a, NUM, sizeof(int), compare);
    qsort(list_b, NUM, sizeof(int), compare);
    int dist = 0;
    for (int i = 0; i < NUM; i++) {
        dist += abs(list_a[i]-list_b[i]);
    }
    printf("%d\n", dist);
    return 0;
}