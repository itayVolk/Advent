/* 
   Author: Itay Volk
   Date: 12/11/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    long long num;
    struct node * next;
} NODE;

int numPlaces (long long n) {
    if (n < 10) return 1;
    return 1 + numPlaces (n / 10);
}

int getIndex(long long * keys, int * numKeys, long long key) {
    for (int i = 0; i < (*numKeys); i++) {
        if (keys[i] == key) {
            return i;
        }
    }
    keys[*numKeys] = key;
    return (*numKeys)++;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char * buffer = malloc(length);
    fread(buffer, 1, length, fp);
    fclose(fp);
    
    int numKeys = 0;
    long long * keys = calloc(pow(10, 10), sizeof(long long));
    long long * counts = calloc(10, sizeof(long long));

    char * tok = strtok(strtok(buffer, "\n"), " ");
    while (tok != NULL) {
        counts[getIndex(keys, &numKeys, (long long)atol(tok))]++;
        tok = strtok(NULL, " ");
    }

    for (int i = 0; i < 75; i++) {
        int size = numKeys;
        long long * curr = calloc(numKeys*3, sizeof(long long));
        for (int j = 0; j < size; j++) {
            if (keys[j] == 0) {
                curr[getIndex(keys, &numKeys, 1)] = counts[j];
            }
            else if (numPlaces(keys[j])%2 == 0) {
                long long power = pow(10, numPlaces(keys[j])/2);
                curr[getIndex(keys, &numKeys, keys[j] % power)] += counts[j];
                curr[getIndex(keys, &numKeys, keys[j] / power)] += counts[j];
            } else {
                curr[getIndex(keys, &numKeys, keys[j]*2024)] += counts[j];
            }
        }
        free(counts);
        counts = curr;
    }
    
    long long count = 0;
    for (long long i = 0; i < numKeys; i++) {
        count += counts[i];
    }
    printf("%lld\n", count);
    return 0;
}