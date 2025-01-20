/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int sum = 0;
    while (fgets(line, sizeof(line), fp)) {
        bool done = false;
        for (int i = 0; i < strlen(line)/2; i++) {
            for (int j = strlen(line)/2; j < strlen(line)-1; j++) {
                if (line[i] == line[j]) {
                    if (line[i] >= 'a') {
                        sum += line[i]-'a'+1;
                    } else {
                        sum += line[i]-'A'+27;
                    }
                    done = true;
                    break;
                }
            }
            if (done) {
                break;
            }
        }
    }
    printf("%d\n", sum);
    return 0;
}