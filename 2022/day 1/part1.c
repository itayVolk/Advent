/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int max = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        int cur = 0;
        do {
            cur += atoi(line);
        } while (fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0);
        if (cur > max) {
            max = cur;
        }
    }
    printf("%d\n", max);
    return 0;
}