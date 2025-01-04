/* 
   Author: Itay Volk
   Date: 01/03/2025
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int total = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        bool * status = calloc(25, sizeof(bool));
        int count = 0;
        int * broken = calloc(25, sizeof(int));
        int numBroken = 0;
        while (line[count] != ' ') {
            status[count] = line[count]=='#';
            if (line[count] == '?') {
                broken[numBroken++] = count;
            }
            count++;
        }
        char * ptr = line;
        char * tok = strtok_s(line+count+1, ",", &ptr);
        int * blocks = calloc(count/2+1, sizeof(int));
        int numBlocks = 0;
        while (tok != NULL) {
            blocks[numBlocks++] = atoi(tok);
            tok = strtok_s(NULL, ",", &ptr);
        }

        for (int i = 0; i < pow(2, numBroken); i++) {
            for (int j = 0; j < numBroken; j++) {
                status[broken[j]] = i/(int)pow(2, j)%2;
            }
            int loc = 0;
            bool add = true;
            for (int j = 0; j < numBlocks; j++) {
                int num = 0;
                while (loc < count && !status[loc]) {
                    num++;
                    loc++;
                }
                if (loc == count || (num == 0 && j != 0)) {
                    add = false;
                    break;
                }
                num = 0;
                for (; num < blocks[j] && loc < count; num++) {
                    if (!status[loc]) {
                        add = false;
                        break;
                    }
                    loc++;
                }
                if (num != blocks[j] || (loc == count && j != numBlocks-1)) {
                    add = false;
                }
                if (!add) {
                    break;
                }
            }
            while (loc < count && !status[loc]) {
                loc++;
            }
            if (add && loc==count) {
                total++;
            }
        }
    }
    printf("%d\n", total);
    return 0;
}