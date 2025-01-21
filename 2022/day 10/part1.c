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
    int n = 0;
    int sum = 0;
    while (fgets(line, sizeof(line), fp)) {
        n++;
        if (line[0] == 'a') {
            if ((n-20)%40 == 0) {
                sum += n*x;
            }
            n++;
            x += atoi(line+5);
        }
        if ((n-20)%40 == 0) {
            sum += n*x;
        }
    }
    printf("%d\n", sum);
    return 0;
}