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
    int max[3] = {0, 0, 0};
    while (fgets(line, sizeof(line), fp) != NULL) {
        int cur = 0;
        do {
            cur += atoi(line);
        } while (fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0);
        if (cur > max[0]) {
            int id = 0;
            if (cur > max[1]) {
                max[0] = max[1];
                id++;
                if (cur > max[2]) {
                    max[1] = max[2];
                    id++;
                }
            }
            max[id] = cur;
        }
    }
    printf("%d\n", max[0]+max[1]+max[2]);
    return 0;
}