/* 
   Author: Itay Volk
   Date: 12/22/2024
*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "pqueue.h"

typedef struct node {
    char * name;
    LIST * adj;
} NODE;

static int compare (NODE * a, char * name) {
    return strcmp(a->name, name);
}

static int compareNodes (NODE * a, NODE * b) {
    return strcmp(a->name, b->name);
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

LIST * findMax(LIST * r, LIST * p, LIST * x) {
    if (numItems(p) == 0 && numItems(x) == 0) {
        LIST * max = createList(compare);
        // printf("1\n");
        addFirst(max, r);
        return max;
    }
    NODE ** nodes = getItems(p);
    LIST * max = createList(compare);
    for (int i = 0; i < numItems(p); i++) {
        LIST * rc = createList(compare);
        NODE ** rn = getItems(r);
        for (int j = 0; j < numItems(r); j++) {
            // printf("2\n");
            addFirst(rc, rn[j]);
        }
        // printf("3\n");
        addFirst(rc, nodes[i]);
        LIST * pc = createList(compare);
        NODE ** pn = getItems(p);
        for (int j = 0; j < numItems(p); j++) {
            if (findItem(nodes[i]->adj, pn[j]->name) != NULL) {
                // printf("4\n");
                addFirst(pc, pn[j]);
            }
        }
        LIST * xc = createList(compare);
        NODE ** xn = getItems(x);
        for (int j = 0; j < numItems(x); j++) {
            if (findItem(nodes[i]->adj, xn[j]->name) != NULL) {
                // printf("5\n");
                addFirst(xc, xn[j]);
            }
        }
        LIST * add = findMax(rc, pc, xc);
        NODE ** addn = getItems(add);
        for (int j = 0; j < numItems(add); j++) {
            // printf("6\n");
            addFirst(max, addn[j]);
        }
        removeItem(p, nodes[i]->name);
        // printf("7\n");
        addFirst(x, nodes[i]);
    }
    return max;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    LIST * nodes = createList(compare);

    while(fgets(line, sizeof(line), fp) != NULL) {
        NODE * a = findItem(nodes, getString(0, 2, line));
        if (a == NULL) {
            a = malloc(sizeof(NODE));
            a->name = getString(0, 2, line);
            a->adj = createList(compare);
            // printf("8\n");
            addFirst(nodes, a);
        }
        NODE * b = findItem(nodes, getString(3, 2, line));
        if (b == NULL) {
            b = malloc(sizeof(NODE));
            b->name = getString(3, 2, line);
            b->adj = createList(compare);
            // printf("9\n");
            addFirst(nodes, b);
        }
        // printf("10\n");
        addFirst(a->adj, b);
        // printf("11\n");
        addFirst(b->adj, a);
    }

    LIST * list = findMax(createList(compare), nodes, createList(compare));
    LIST * max = NULL;
    while (numItems(list) > 0) {
        LIST * cur = removeFirst(list);
        if (max == NULL || numItems(max) < numItems(cur)) {
            max = cur;
        }
    }

    PQ * pq = createQueue(compareNodes);
    while (numItems(max) > 0) {
        addEntry(pq, getFirst(max));
        removeFirst(max);
    }

    while (numEntries(pq) > 0) {
        printf("%s,", ((NODE *)removeEntry(pq))->name);
    }
    return 0;
}