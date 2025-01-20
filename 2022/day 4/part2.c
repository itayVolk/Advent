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
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        int s1 = atoi(strtok(line, "-"));
        int e1 = atoi(strtok(NULL, ","));
        int s2 = atoi(strtok(NULL, "-"));
        int e2 = atoi(strtok(NULL, "-"));
        if ((s1<=s2 && s2<=e1) || (s1<=e2 && e2<=e1) || (s2<=s1 && s1<=e2) || (s2<=e1 && e1<=e2)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}