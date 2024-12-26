/* 
   Author: Itay Volk
   Date: 12/26/2024
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static char *digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int findDigit(char * str, int dir) {
    while (true) {
        if (isdigit(str[0])) {
            return str[0]-'0';
        }
        for (int i = 0; i < 9; i++) {
            int j = 0;
            while (digits[i][j] == str[j]) {
                j++;
            }
            if (digits[i][j] == '\0') {
                return i+1;
            }
        }
        str += dir;
    }
    return -1;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        sum += findDigit(line, 1)*10 + findDigit(line+strlen(line), -1);
    }
    printf("%d\n", sum);
    return 0;
}