/* 
   Author: Itay Volk
   Date: 12/27/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    // int sum = 0;
    int id = 0;
    int sum = 0;
    int * counts = calloc(256, sizeof(int));
    while(fgets(line, sizeof(line), fp) != NULL) {
        counts[id]++;
        sum += counts[id];
        char * pre = strtok(strstr(line, ":")+2, "|");
        char * post = strtok(NULL, "|");
        char * tok = strtok(pre, " ");
        int count = 0;
        int * exist = calloc(10, sizeof(int));
        while (tok != NULL) {
            exist[count++] = atoi(tok);
            tok = strtok(NULL, " ");
        }
        int num = 0;
        tok = strtok(post, " ");
        while(tok != NULL) {
            int cur = atoi(tok);
            tok = strtok(NULL, " ");
            for (int i = 0; i < count; i++) {
                if (exist[i] == cur) {
                    num++;
                    break;
                }
            }
        }
        for (int i = id+1; i <= id+num; i++) {
            counts[i] += counts[id];
        }
        id++;
    }
    printf("%d\n", sum);
    return 0;
}