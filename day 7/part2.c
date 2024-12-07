/* 
   Author: Itay Volk
   Date: 12/07/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

unsigned long long * possible(int * arr, int length) {
    if (length == 1) {
        unsigned long long *out = calloc(1, sizeof(long));
        out[0] = arr[0];
        return out;
    }
    int count = (int)pow(3, length-2);
    unsigned long long * out = calloc(3*count, sizeof(unsigned long long));
    unsigned long long * child = possible(arr+1, length-1);
    memmove(out, child, count*sizeof(unsigned long long));
    memmove(out+count, child, count*sizeof(unsigned long long));
    memmove(out+count*2, child, count*sizeof(unsigned long long));
    for(int i = 0; i < count; i++) {
        out[i] += arr[0];
        out[i+count] *= arr[0];
        // printf("%lld+%d=", out[i+count*2], arr[0]);
        char concat[256];
        sprintf(concat, "%llu%d", out[i+count*2], arr[0]);
        out[i+count*2] = atoll(concat);
        // printf("%lld\n", out[i+count*2]);
    }
    return out;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    long long sum = 0;
    long long prev = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        unsigned long long tot = (unsigned long long)atoll(strtok(line, ":"));
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
        unsigned long long * options = possible(arr, l);
        for (int i = 0; i < pow(3, l-1); i++) {
            if (options[i] == tot) {
                pos = true;
                break;
            }
        }

        if (pos) {
            prev = sum;
            sum += tot;
        }
    }
    printf("%llu\n", sum);
    return 0;
}