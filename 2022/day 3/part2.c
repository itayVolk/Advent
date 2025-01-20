/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int check(char start, char * lines[3]) {
    for (char c = start; c <= start+26; c++) {
        bool match = true;
        for (int i = 0; i < 3; i++) {
            bool temp = false;
            for (int j = 0; j < strlen(lines[i]); j++) {
                if (lines[i][j] == c) {
                    temp = true;
                    break;
                }
            }
            if (!temp) {
                match = false;
                break;
            }
        }
        if (match) {
            return c-start;
        }
    }
    return -1;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int sum = 0;
    while (fgets(line, sizeof(line), fp)) {
        char * lines[3];
        int i = 0;
        do {
            lines[i] = calloc(strlen(line), sizeof(char));
            for (int j = 0; j < strlen(line)-1; j++) {
                lines[i][j] = line[j];
            }
            i++;
        } while(i < 3 && fgets(line, sizeof(line), fp));

        int low = check('a', lines);
        if (low != -1) {
            sum += low+1;
        } else {
            sum += check('A', lines)+27;
        }
    }
    printf("%d\n", sum);
    return 0;
}