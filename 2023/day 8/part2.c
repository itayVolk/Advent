/* 
   Author: Itay Volk
   Date: 12/29/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "list.h"

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

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char moves[512];
    fgets(moves, sizeof(moves), fp);
    char line[256];
    fgets(line, sizeof(line), fp);

    SET * nodes = createSet(800, compare, hash);
    LIST * a = createList(NULL);
    while(fgets(line, sizeof(line), fp) != NULL) {
        NODE * add = addNode(nodes, getString(0, 3, line));
        add->left = addNode(nodes, getString(7, 3, line));
        add->right = addNode(nodes, getString(12, 3, line));
        if (add->name[2] == 'A') {
            addFirst(a, add);
        }
    }

    int *steps = calloc(numItems(a), sizeof(int));
    int num = numItems(a);
    for (int i = 0; i < num; i++) {
        NODE * run = removeFirst(a);
        while (run->name[2] != 'Z') {
            if (moves[steps[i]%(strlen(moves)-1)] == 'L') {
                run = run->left;
            } else {
                run = run->right;
            }
            steps[i]++;
        }
    }

    long long lcm = steps[0];
    for (int i = 1; i < num; i++) {
        lcm = lcm*steps[i]/gcd(lcm, steps[i]);
    }
    printf("%lld\n", lcm);
    return 0;
}