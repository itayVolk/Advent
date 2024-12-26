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
    int id = 1;
    while(fgets(line, sizeof(line), fp) != NULL) {
        char * tok = strtok(strstr(line, ":")+2, " ");
        bool possible = true;
        while (tok != NULL && possible) {
            int num = atoi(tok);
            tok = strtok(NULL, " ");
            switch (tok[0]) {
                case 'r':
                    if (num > 12) {
                        possible = false;
                    }
                    break;
                case 'g':
                    if (num > 13) {
                        possible = false;
                    }
                    break;
                case 'b':
                    if (num > 14) {
                        possible = false;
                    }
                    break;
            }
            tok = strtok(NULL, " ");
        }
        if (possible) {
            sum += id;
        }
        id++;
    }
    printf("%d\n", sum);
    return 0;
}