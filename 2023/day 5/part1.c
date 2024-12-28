/* 
   Author: Itay Volk
   Date: 12/27/2024
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    long long * cur = calloc(25, sizeof(long long));
    fgets(line, sizeof(line), fp);
    char * seed = strtok(strstr(line, ":")+2, " ");
    int count = 0;
    while (seed != NULL) {
        cur[count++] = atoll(seed);
        seed = strtok(NULL, " ");
    }

    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL) {
        long long * next = malloc(count*sizeof(long long));
        for (int i = 0; i < count; i++) {
            next[i] = -1;
        }
        while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
            long long dest = atoll(strtok(line, " "));
            long long source = atoll(strtok(NULL, " "));
            long long length = atoll(strtok(NULL, " "));
            for (int i = 0; i < count; i++) {
                if (cur[i] >= source && cur[i] < source+length) {
                    next[i] = cur[i]-source+dest;
                }
            }
        }
        for (int i = 0; i < count; i++) {
            if (next[i] == -1) {
                next[i] = cur[i];
            }
        }
        cur = next;
    }

    long long min = LONG_LONG_MAX;
    for (int i = 0; i < count; i++) {
        if (cur[i] < min) {
            min = cur[i];
        }
    }
    printf("%lld\n", min);
    return 0;
}