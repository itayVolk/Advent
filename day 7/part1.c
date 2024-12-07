/* 
   Author: Itay Volk
   Date: 12/07/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

long long * possible(int * arr, int length) {
    if (length == 1) {
        long long *out = calloc(1, sizeof(long));
        out[0] = arr[0];
        return out;
    }
    int count = (int)pow(2, length-2);
    long long * out = calloc(2*count, sizeof(long long));
    long long * child = possible(arr+1, length-1);
    memmove(out, child, count*sizeof(long long));
    memmove(out+count, child, count*sizeof(long long));
    for(int i = 0; i < count; i++) {
        out[i] += arr[0];
        out[i+count] *= arr[0];
    }
    return out;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    unsigned long long sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        long long tot = atoll(strtok(line, ":"));
        int *arr = calloc(15, sizeof(int));
        
        char * token = strtok(NULL, " ");
        int l = 0;
        while (token != NULL) {
            arr[l++] = atoi(token);
            token = strtok(NULL, " ");
        }
        
        bool pos = false;
        for (int i = 0; i < l/2; i++) {
            int temp = arr[i];
            arr[i] = arr[l-i-1];
            arr[l-i-1] = temp;
        }
        long long * options = possible(arr, l);
        for (int i = 0; i < pow(2, l-1); i++) {
            if (options[i] == tot) {
                pos = true;
                break;
            }
        }

        if (pos) {
            sum += tot;
        }
    }
    printf("%llu\n", sum);
    return 0;
}