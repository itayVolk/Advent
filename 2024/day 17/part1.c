/* 
   Author: Itay Volk
   Date: 12/16/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

char * getString(int pos, int len, char string[])
{
    if (len == -1) {
        len = strlen(string)-pos;
    }
    char * substring = calloc(len+1, sizeof(char));
    int i = 0;
    while (i < len) {
        substring[i] = string[pos + i];
        i++;
    }
    return substring;
}

long long combo(int i, long long reg[3]) {
    if (i <= 3) {
        return i;
    }
    if (i <= 6) {
        return reg[i-4];
    }
    printf("INVALID");
    return -1;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    long long reg[3];
    for (int i = 0; i < 3; i++) {
        fgets(line, sizeof(line), fp);
        reg[i] = atoll(getString(12, -1, line));
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    char * tok = strtok(getString(9, -1, line), ",");
    int nums[20];
    int count = 0;
    while (tok != NULL) {
        nums[count++] = atoi(tok);
        tok = strtok(NULL, ",");
    }

    for (int i = 0; i < count; i += 2) {
        switch(nums[i]) {
            case 0:
                reg[0] = reg[0]/pow(2, combo(nums[i+1], reg));
                break;
            case 1:
                reg[1] = reg[1]^nums[i+1];
                break;
            case 2:
                reg[1] = combo(nums[i+1], reg)%8;
                break;
            case 3:
                if (reg[0] != 0) {
                    i = nums[i+1]-2;
                    // printf("%lld\n", reg[0]);
                }
                break;
            case 4:
                reg[1] = reg[1]^reg[2];
                break;
            case 5:
                printf("%lld,", combo(nums[i+1], reg)%8);
                break;
            case 6:
            case 7:
                reg[nums[i]-5] = reg[0]/pow(2, combo(nums[i+1], reg));
                break;
        }
    }

    return 0;
}