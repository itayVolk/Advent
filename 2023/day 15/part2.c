/* > 501594
   Author: Itay Volk
   Date: 01/05/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct lens {
    char * label;
    int num;
} LENS;

#define MAX 256

static int compare(LENS * a, char * b) {
    return strcmp(a->label, b);
}

int hash (char * str) {
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '\n') {
            break;
        }
        hash += str[i];
        hash *= 17;
        hash %= MAX;
    }
    return hash;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[25000];
    fgets(line, sizeof(line), fp);
    char * ptr = line;
    char * tok = strtok_s(line, ",", &ptr);

    LIST ** map = malloc(MAX*sizeof(LIST *));
    for (int i = 0; i < MAX; i++) {
        map[i] = createList(compare);
    }

    while (tok != NULL) {
        char * label = calloc(strlen(tok)-1, sizeof(char));
        while(tok[0] >= 'a') {
            label[strlen(label)] = tok[0];
            tok++;
        }

        if (tok[0] == '-') {
            removeItem(map[hash(label)], label);
        } else {
            LENS * found = findItem(map[hash(label)], label);
            if (found == NULL) {
                found = malloc(sizeof(LENS));
                found->label = label;
                addLast(map[hash(label)], found);
            }
            found->num = tok[1]-'0';
        }
        tok = strtok_s(NULL, ",", &ptr);
    }

    long long sum = 0;
    for (int i = 0; i < MAX; i++) {
        LENS ** items = getItems(map[i]);
        for (int j = 0; j < numItems(map[i]); j++) {
            sum += (i+1)*(j+1)*items[j]->num;
        }
    }
    printf("%lld\n", sum);
    return 0;
}