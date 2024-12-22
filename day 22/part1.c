/* 
   Author: Itay Volk
   Date: 12/21/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PRUNE(code) ((code)%16777216)

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    long long sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        long long code = atoll(line);
        for (int i = 0; i < 2000; i++) {
            code = PRUNE(code*64^code);
            code = PRUNE(code/32^code);
            code = PRUNE(code*2048^code);
        }
        sum += code;
    }
    printf("%lld\n", sum);
    return 0;
}