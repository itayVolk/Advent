/* 
   Author: Itay Volk
   Date: 12/22/2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HASH_MAX 676

int hash(char * str) {
    return str[0]-'a' + (str[1]-'a')*26;
}

char * getString(int pos, int len, char string[]) {
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

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    bool ** adj = malloc(HASH_MAX*sizeof(bool*));
    for (int i = 0; i < HASH_MAX; i++) {
        adj[i] = calloc(HASH_MAX, sizeof(bool));
    }

    while(fgets(line, sizeof(line), fp) != NULL) {
        int a = hash(getString(0, 2, line));
        int b = hash(getString(3, 2, line));
        adj[a][b] = true;
        adj[b][a] = true;
    }

    int count = 0;
    for (int i = 0; i < HASH_MAX; i++) {
        for (int j = i+1; j < HASH_MAX; j++) {
            if (adj[i][j]) {
                for (int k = j+1; k < HASH_MAX; k++) {
                    if (adj[i][k] && adj[j][k] && (i%26=='t'-'a' || j%26=='t'-'a' || k%26=='t'-'a')) {
                        count++;
                    }
                }
            }
        }
    }

    printf("%d\n", count);
    return 0;
}