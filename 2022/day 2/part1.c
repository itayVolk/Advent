/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int score = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        score += line[2]-'X'+1 + (line[2]-'X'-line[0]+'A'+4)%3*3;
    }
    printf("%d\n", score);
    return 0;
}