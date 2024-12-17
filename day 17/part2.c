/* 
   Author: Itay Volk
   Date: 12/16/2024
*/

#include <stdio.h>
#include <assert.h>
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

bool check(long long a, int nums[20], int count, int i) {
    for (; i < count; i++) {
        if ((a%8^5^6^(long long)(a/pow(2, a%8^5))%8) != nums[i]) {
            // printf("i%d:%lld:%di", i, a%8^5^6^(long long)(a/pow(2, a%8^5))%8, nums[i]);
            return false;
        }
        a /= 8;
        // printf("a%llda", a);
    }
    return true;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);
    char * tok = strtok(getString(9, -1, line), ",");
    int nums[20];
    int count = 0;
    while (tok != NULL) {
        nums[count++] = atoi(tok);
        tok = strtok(NULL, ",");
    }

    long long a = 0;
    for (int i = count-1; i >= 0; i--) {
        a *= 8;
        printf("%d:", nums[i]);
        int num = 0;
        while(!check(a, nums, count, i)) {
            printf("%lld,", a%8^5^6^(long long)(a/pow(2, a%8^5))%8);
            a++;
            num++;
            // assert(num < 8);
        }
        printf(",%lld\n", a);
    }
    printf("%lld\n", a);

    return 0;
}