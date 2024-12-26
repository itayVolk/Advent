/* 
   Author: Itay Volk
   Date: 12/24/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void readLn(char * line, int * read) {
    for (int i = 0; i < strlen(line)-1; i++) {
        if (line[i] == '#') {
            read[i]++;
        }
    }
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int ** locks = calloc(500, sizeof(int*));
    int locksNum = 0;
    int ** keys = calloc(500, sizeof(int*));
    int keysNum = 0;

    while(fgets(line, sizeof(line), fp) != NULL) {
        if (strcmp(line, "#####\n") == 0) {
            locks[locksNum] = calloc(5, sizeof(int));
            while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
                readLn(line, locks[locksNum]);
            }
            locksNum++;
        } else {
            keys[keysNum] = calloc(5, sizeof(int));
            do {
                readLn(line, keys[keysNum]);
            } while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0);
            for (int i = 0; i < 5; i++) {
                keys[keysNum][i]--;
            }
            keysNum++;
        }
    }

    int count = 0;
    for (int i = 0; i < locksNum; i++) {
        for (int j = 0; j < keysNum; j++) {
            bool match = true;
            for (int k = 0; k < 5; k++) {
                if (locks[i][k] + keys[j][k] > 5) {
                    match = false;
                    break;
                }
            }
            if (match) {
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}