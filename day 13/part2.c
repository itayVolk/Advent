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

    long long sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int xa = atoi(getString(12, 2, line));
        int ya = atoi(getString(18, 2, line));
        fgets(line, sizeof(line), fp);
        int xb = atoi(getString(12, 2, line));
        int yb = atoi(getString(18, 2, line));
        fgets(line, sizeof(line), fp);
        double x = atoi(strtok(getString(9,-1, line), ","))+10000000000000l;
        double y = atoi(getString(3, -1, strtok(NULL, ",")))+10000000000000l;
        fgets(line, sizeof(line), fp);

        double b = (xa*y-x*ya)/(xa*yb-xb*ya);
        double a = (x-b*xb)/xa;
        if ((long long)a == a && (long long)b == b) {
            sum += (long long)(a*3+b);
            printf("%lf:%lf\n", a, b);
        }
    }
    printf("%lld\n", sum);
    return 0;
}