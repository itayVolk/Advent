/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[5000];

    while (fgets(line, sizeof(line), fp)) {
        for (int i = 14; i < strlen(line); i++) {
            bool pass = true;
            for (int j = i-14; j < i; j++) {
                for (int k = j+1; k < i; k++) {
                    if (line[j] == line[k]) {
                        pass = false;
                        break;
                    }
                }
                if (!pass) {
                    break;
                }
            }
            if (pass) {
                printf("%d\n", i);
                return 0;
            }
        }
    }
    return 0;
}