/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int x = 1;
    int n = 1;
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", abs(x-n%40+1) <= 1 ? "[]" : "  ");
        if (n%40 == 0) {
            printf("\n");
        }
        n++;
        if (line[0] == 'a') {
            printf("%s", abs(x-n%40+1) <= 1 ? "[]" : "  ");
            if (n%40 == 0) {
                printf("\n");
            }
            n++;
            x += atoi(line+5);
        }
    }
    return 0;
}