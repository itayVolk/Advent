/* 
   Author: Itay Volk
   Date: 01/18/2025
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"
#include "pqueue.h"

typedef struct node {
    char * name;
    int id;
    int numEdges;
    struct node ** edges;
} NODE;

typedef struct edge {
    NODE ** edge;
    int val;
} EDGE;

typedef struct loc {
    NODE * node;
    int val;
} LOC;

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

static int compareNames(NODE * a, NODE * b) {
    return strcmp(a->name, b->name);
}

static unsigned hash(NODE * a) {
    unsigned hash = 0;
    for (int i = 0; i < strlen(a->name); i++) {
        hash += a->name[i];
    }
    return hash;
}

static int compareEdges(EDGE * a, EDGE * b) {
    return b->val-a->val;
}

static int compareLocs(LOC * a, LOC * b) {
    return a->val-b->val;
}

NODE * createNode(SET * nodes, char * node) {
    NODE * search = malloc(sizeof(NODE));
    search->name = calloc(4, sizeof(char));
    memcpy(search->name, node, 3*sizeof(char));
    NODE * found = findElement(nodes, search);
    if (found == NULL) {
        search->id = numElements(nodes);
        search->numEdges = 0;
        search->edges = malloc(20*sizeof(NODE *));
        addElement(nodes, search);
        return search;
    }
    return found;
}

bool removed(NODE *** r, NODE * a, NODE * b) {
    for (int i = 0; i < 3; i++) {
        if ((r[i][0]==a && r[i][1]==b) || (r[i][0]==b && r[i][1]==a)) {
            return true;
        }
    }
    return false;
}

int countNodes(NODE * loc, NODE *** r, bool * visited) {
    if (visited[loc->id]) {
        return 0;
    }

    visited[loc->id] = true;
    int count = 1;
    for (int i = 0; i < loc->numEdges; i++) {
        if (!removed(r, loc, loc->edges[i])) {
            count += countNodes(loc->edges[i], r, visited);
        }
    }
    return count;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    SET * nodes = createSet(2000, compareNames, hash);
    NODE *** edges = malloc(4000*sizeof(NODE **));
    int numEdges = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        NODE * cur = createNode(nodes, getString(0, 3, line));
        char * add = strtok(line+4, " ");
        while (add != NULL) {
            NODE * connect = createNode(nodes, add);
            edges[numEdges] = malloc(2*sizeof(NODE *));
            edges[numEdges][0] = cur;
            edges[numEdges++][1] = connect;
            cur->edges[cur->numEdges++] = connect;
            connect->edges[connect->numEdges++] = cur;
            add = strtok(NULL, " ");
        }
    }
    
    int num = numElements(nodes);
    PQ * pq = createQueue(compareEdges);
    for (int i = 0; i < numEdges; i++) {
        PQ * paths = createQueue(compareLocs);
        int * vals = malloc(num*sizeof(int));
        for (int j = 0; j < num; j++) {
            vals[j] = INT_MAX;
        }
        LOC * cur = malloc(sizeof(LOC));
        cur->node = edges[i][0];
        cur->val = 0;
        while(cur->node != edges[i][1]) {
            vals[cur->node->id] = cur->val;
            for (int j = 0; j < cur->node->numEdges; j++) {
                if ((edges[i][0]!=cur->node || edges[i][1]!=cur->node->edges[j]) && (edges[i][0]!=cur->node->edges[j] || edges[i][1]!=cur->node)) {
                    LOC * add = malloc(sizeof(LOC));
                    add->node = cur->node->edges[j];
                    add->val = cur->val+1;
                    addEntry(paths, add);
                }
            }

            do {
                cur = removeEntry(paths);
            } while (vals[cur->node->id] <= cur->val);
        }
        EDGE * insert = malloc(sizeof(EDGE));
        insert->edge = edges[i];
        insert->val = cur->val;
        addEntry(pq, insert);
    }
    for (int i = 0; i < numEdges; i++) {
        EDGE * edge = removeEntry(pq);
        edges[i] = edge->edge;
    }

    for (int i = 0; i < numEdges; i++) {
        for (int j = i+1; j < numEdges; j++) {
            for (int k = j+1; k < numEdges; k++) {
                NODE ** r[3] = {edges[i], edges[j], edges[k]};
                bool * visited = calloc(num, sizeof(bool));
                int count = countNodes(edges[i][0], r, visited);
                free(visited);
                if (count != num) {
                    printf("%d\n", count*(num-count));
                    return 0;
                }
            }
        }
    }
    return 0;
}