/* 
   Author: Itay Volk
   Date: 12/31/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int extend(int ** nums, int count, int depth) {
    nums[depth+1] = calloc(count, sizeof(int));
    bool end = true;
    for (int i = 1; i < count; i++) {
        nums[depth+1][i] = nums[depth][i+1]-nums[depth][i];
        if (nums[depth+1][i] != 0) {
            end = false;
        }
    }
    if (end) {
        return 0;
    }
    return extend(nums, count-1, depth+1)+1;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int **nums = malloc(30*sizeof(int *));
        nums[0] = calloc(30, sizeof(int));
        int count = 0;
        char * ptr = line;
        char * tok = strtok_s(line, " ", &ptr);
        while (tok != NULL) {
            nums[0][1+count++] = atoi(tok);
            tok = strtok_s(NULL, " ", &ptr);
        }
        int depth = extend(nums, count, 0);
        for (; depth >= 0; depth--) {
            nums[depth][0] = nums[depth][1] - nums[depth+1][0];
        }
        sum += nums[0][0];
    }
    printf("%d\n", sum);
    return 0;
}