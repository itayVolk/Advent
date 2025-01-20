/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int score = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        score += (line[0]-'A'+line[2]-'X'+2)%3+1 + (line[2]-'X')*3;
    }
    printf("%d\n", score);
    return 0;
}