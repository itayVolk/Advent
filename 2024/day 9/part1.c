/* 
   Author: Itay Volk
   Date: 12/03/2024
*/

#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char * buffer = malloc(length);
    fread(buffer, 1, length, fp);
    fclose(fp);

    int * arr = calloc(100000, sizeof(int));
    int loc = 0;
    for (int i = 0; i < length/2-1; i++) {
        for (int j = 0; j < buffer[2*i]-'0'; j++) {
            arr[loc++] = i;
        }
        for (int j = 0; j < buffer[2*i+1]-'0'; j++) {
            arr[loc++] = -1;
        }
    }
    for (int j = 0; j < buffer[length-2]-'0'; j++) {
        arr[loc++] = length/2-1;
    }

    int empty = 0;
    int move = loc-1;
    while (empty < move) {
        while(arr[empty] != -1) {
            empty++;
        }
        while(arr[move] == -1) {
            move--;
        }
        if (empty < move) {
            arr[empty] = arr[move];
            arr[move] = -1;
        }
    }
    unsigned long long sum = 0;
    for (int i = 1; arr[i] != -1; i++) {
        sum += arr[i]*i;
    }
    printf("%llu\n", sum);
    return 0;
}