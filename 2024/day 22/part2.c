/* 
   Author: Itay Volk
   Date: 12/21/2024
*/

#include <stdio.h>
#include <stdlib.h>

#define PRUNE(code) ((code)%16777216)
#define MAX_HASH 130321

int hashing(int * changes) {
    int hash = 0;
    for (int i = 0; i < 4; i++) {
        hash *= 19;
        hash += changes[i]+9;
    }
    return hash;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int ** values = malloc(MAX_HASH*sizeof(int *));
    for (int i = 0; i < MAX_HASH; i++) {
        values[i] = malloc(2500*sizeof(int));
        for (int j = 0; j < 2500; j++) {
            values[i][j] = -1;
        }
    }

    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        long long code = atoll(line);
        int changes[4];
        for (int i = 0; i < 2000; i++) {
            int prev = code%10;
            code = PRUNE(code*64^code);
            code = PRUNE(code/32^code);
            code = PRUNE(code*2048^code);
            for (int j = 3; j > 0; j--) {
                changes[j] = changes[j-1];
            }
            changes[0] = code%10-prev;
            if (i >= 3) {
                int hash = hashing(changes);
                if (values[hash][count] == -1) {
                    values[hash][count] = code%10;
                }
            }
        }
        count++;
    }

    int score = 0;
    for (int i = 0; i < MAX_HASH; i++) {
        int sum = 0;
        for (int j = 0; j < count; j++) {
            if (values[i][j] != -1) {
                sum += values[i][j];
            }
        }
        if (sum > score) {
            score = sum;
        }
    }
    printf("%d\n", score);
    return 0;
}