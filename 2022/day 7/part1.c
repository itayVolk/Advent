/* 
   Author: Itay Volk
   Date: 01/20/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct dir {
    char * name;
    int size;
    struct dir * parent;
    LIST * sub;
} DIR;

static int compare(DIR * a, DIR * b) {
    return strcmp(a->name, b->name);
}

int addSub(DIR * d) {
    DIR ** sub = getItems(d->sub);
    for (int i = 0; i < numItems(d->sub); i++) {
        d->size += addSub(sub[i]);
    }
    return d->size;
}

int countSub(DIR * d) {
    int sum = d->size < 100000 ? d->size : 0;
    DIR ** sub = getItems(d->sub);
    for (int i = 0; i < numItems(d->sub); i++) {
        sum += countSub(sub[i]);
    }
    return sum;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    DIR * home = malloc(sizeof(DIR));
    home->name = "/";
    home->parent = NULL;
    home->size = 0;
    home->sub = createList(compare);
    DIR * cur = home;

    while(fgets(line, sizeof(line), fp)) {
        if (line[0] == '$') {
            if (line[2] == 'c') {
                if (line[5] == '/') {
                    cur = home;
                } else if (line[5] == '.') {
                    cur = cur->parent;
                } else {
                    DIR * new = malloc(sizeof(DIR));
                    new->name = calloc(strlen(line)-5, sizeof(char));
                    memccpy(new->name, line+5, strlen(line)-6, (strlen(line)-6)*sizeof(char));
                    DIR * found = findItem(cur->sub, new);
                    if (found == NULL) {
                        found = new;
                        found->size = 0;
                        found->parent = cur;
                        found->sub = createList(compare);
                        addLast(cur->sub, found);
                    }
                    cur = found;
                }
            }
        } else if (line[0] != 'd') {
            cur->size += atoi(strtok(line, " "));
        }
    }

    addSub(home);
    printf("%d\n", countSub(home));
    return 0;
}