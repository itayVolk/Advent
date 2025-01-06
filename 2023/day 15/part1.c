/* > 501594
   Author: Itay Volk
   Date: 01/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[25000];
    fgets(line, sizeof(line), fp);
    char * ptr = line;
    char * tok = strtok_s(line, ",", &ptr);

    long long sum = 0;
    while (tok != NULL) {
        int hash = 0;
        for (int i = 0; i < strlen(tok); i++) {
            if (tok[i] == '\n') {
                break;
            }
            hash += tok[i];
            hash *= 17;
            hash %= 256;
        }
        sum += hash;
        tok = strtok_s(NULL, ",", &ptr);
    }
    printf("%lld\n", sum);
    return 0;
}