/* 
   Author: Itay Volk
   Date: 12/29/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

typedef struct node {
    char * name;
    struct node * left;
    struct node * right;
} NODE;

static int compare(NODE * a, NODE * b) {
    return strcmp(a->name, b->name);
}

static unsigned hash(NODE *s)
{
    unsigned hash = 0;
    for (int i = 0; i < strlen(s->name); i++) {
        hash = 31 * hash + s->name[i];
    }
    return hash;
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

NODE * addNode(SET * nodes, char * name) {
    NODE * add = malloc(sizeof(NODE));
    add->name = name;
    NODE * found = findElement(nodes, add);
    if (found == NULL) {
        addElement(nodes, add);
        return add;
    }
    free(add);
    return found;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char moves[512];
    fgets(moves, sizeof(moves), fp);
    char line[256];
    fgets(line, sizeof(line), fp);

    SET * nodes = createSet(800, compare, hash);
    NODE * a = NULL;
    NODE * z = NULL;
    while(fgets(line, sizeof(line), fp) != NULL) {
        NODE * add = addNode(nodes, getString(0, 3, line));
        add->left = addNode(nodes, getString(7, 3, line));
        add->right = addNode(nodes, getString(12, 3, line));
        if (strcmp(add->name, "AAA") == 0) {
            a = add;
        } else if (strcmp(add->name, "ZZZ") == 0) {
            z = add;
        }
    }

    int steps = 0;
    while (a != z) {
        if(moves[steps%(strlen(moves)-1)] == 'L') {
            a = a->left;
        } else {
            a = a->right;
        }
        steps++;
    }
    printf("%d\n", steps);
    return 0;
}