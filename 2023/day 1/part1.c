/* 
   Author: Itay Volk
   Date: 12/26/2024
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int a = 0;
        while (!isdigit(line[a])) {
            a++;
        }
        int b = strlen(line)-2;
        while (!isdigit(line[b])) {
            b--;
        }
        sum += (line[a]-'0')*10 + line[b]-'0';
    }
    printf("%d\n", sum);
    return 0;
}