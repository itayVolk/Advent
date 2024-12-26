/* 
   Author: Itay Volk
   Date: 12/26/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        char * tok = strtok(strstr(line, ":")+2, " ");
        int r = 0;
        int g = 0;
        int b = 0;
        while (tok != NULL) {
            int num = atoi(tok);
            tok = strtok(NULL, " ");
            switch (tok[0]) {
                case 'r':
                    if (num > r) {
                        r = num;
                    }
                    break;
                case 'g':
                    if (num > g) {
                        g = num;
                    }
                    break;
                case 'b':
                    if (num > b) {
                        b = num;
                    }
                    break;
            }
            tok = strtok(NULL, " ");
        }
        sum += r*g*b;
    }
    printf("%d\n", sum);
    return 0;
}