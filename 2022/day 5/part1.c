/* 
   Author: Itay Volk
   Date: 01/19/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    int size;
    LIST ** stacks = NULL;

    while (fgets(line, sizeof(line), fp) && line[1] != '1') {
        if (stacks == NULL) {
            size = strlen(line)/4;
            stacks = malloc(size*sizeof(LIST *));
            for (int i = 0; i < size; i++) {
                stacks[i] = createList(NULL);
            }
        }
        for (int i = 0; i < size; i++) {
            if (line[i*4+1] != ' ') {
                char *c = malloc(sizeof(char));
                *c = line[i*4+1];
                addLast(stacks[i], c);
            }
        }
    }

    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp)) {
        int count = atoi(strtok(line+5, " from "));
        char * clean = strtok(NULL, "\n");
        for (int i = 0; i < count; i++) {
            addFirst(stacks[clean[10]-'1'], removeFirst(stacks[clean[5]-'1']));
        }
    }
    
    for (int i = 0; i < size; i++) {
        printf("%c", *(char *)(getFirst(stacks[i])));
    }
    printf("\n");
    return 0;
}