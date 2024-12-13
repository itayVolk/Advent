/* 
   Author: Itay Volk
   Date: 12/12/2024
*/

#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

char * getString(int pos, int len, char string[])
{
    if (len == -1) {
        len = strlen(string)-pos;
    }
    char * substring = calloc(len+1, sizeof(char));
    int i = 0;
    while (i < len) {
        substring[i] = string[pos + i];
        i++;
    }
    return substring;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int xa = atoi(getString(12, 2, line));
        int ya = atoi(getString(18, 2, line));
        fgets(line, sizeof(line), fp);
        int xb = atoi(getString(12, 2, line));
        int yb = atoi(getString(18, 2, line));
        fgets(line, sizeof(line), fp);
        int x = atoi(strtok(getString(9,-1, line), ","));
        int y = atoi(getString(3, -1, strtok(NULL, ",")));
        fgets(line, sizeof(line), fp);

        int a = -1;
        do {
            a++;
            while (a < 100 && xa*a < x && ya*a < y && ((x-xa*a)%xb != 0 || (y-ya*a)%yb != 0)) {
                a++;
            }
            int b = 0;
            while (b < 100 && xa*a+xb*b < x && ya*a+yb*b < y) {
                b++;
            }
            if (xa*a+xb*b == x && ya*a+yb*b == y) {
                printf("i");
                sum += 3*a + b;
                break;
            }
            printf("%d:%d\n", a, b);
        } while (a < 100);
    }
    printf("%d\n", sum);
    return 0;
}