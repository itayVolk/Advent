/* 
   Author: Itay Volk
   Date: 12/03/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

int main() {
    char *str = "mul(";
    FILE * fp = fopen("input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char * buffer = malloc(length);
    fread(buffer, 1, length, fp);
    fclose(fp);
    char * found = strstr(buffer, str);
    int sum = 0;
    while(found != NULL) {
        found += 4;
        int count = 0;
        char *a = calloc(100, sizeof(char));
        while(isdigit(found[0])) {
            a[count++] = found[0];
            a[count] = '\0';
            found++;
        }
        if (found[0] == ',') {
            found++;
            char *b = calloc(100, sizeof(char));
            count = 0;
            while(isdigit(found[0])) {
                b[count++] = found[0];
                b[count] = '\0';
                found++;
            }
            if (found[0] == ')') {
                sum += atoi(a)*atoi(b);
            }
            found++;
        }
        found = strstr(found, str);
    }

    printf("%d\n", sum);
    return 0;
}