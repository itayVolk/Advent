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
    int * size = calloc(20000, sizeof(int));
    int * locs = calloc(20000, sizeof(int));
    int loc = 0;
    for (int i = 0; i < length/2-1; i++) {
        locs[2*i] = loc;
        for (int j = 0; j < buffer[2*i]-'0'; j++) {
            arr[loc++] = i;
        }
        locs[2*i+1] = loc;
        size[2*i+1] = buffer[2*i+1]-'0';
        for (int j = 0; j < buffer[2*i+1]-'0'; j++) {
            arr[loc++] = -1;
        }
    }
    locs[length-2] = loc;
    for (int j = 0; j < buffer[length-2]-'0'; j++) {
        arr[loc++] = length/2-1;
    }

    int move = length-2;
    while (move >= 0) {
        int insert = 1;
        while (move >= 0) {
            int temp = insert;
            while(temp < move && size[temp] < buffer[move]-'0') {
                temp += 2;
            }
            if (temp < move) {
                insert = temp;
                break;
            }
            move -= 2;
        }
        if (move < 0) 
            break;
        for (int i = 0; i < buffer[move]-'0'; i++) {
            arr[locs[insert]+i] = arr[locs[move]+i];
            arr[locs[move]+i] = -1;
        }
        locs[insert] += buffer[move]-'0';
        size[insert] -= buffer[move]-'0';
        move -= 2;
    }

    unsigned long long sum = 0;
    for (int i = 1; i < loc; i++) {
        if (arr[i] != -1) {
            sum += arr[i]*i;
        }
    }
    printf("%llu\n", sum);
    return 0;
}