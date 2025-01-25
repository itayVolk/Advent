/* 
   Author: Itay Volk
   Date: 01/24/2025
*/

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "table.h"
#include "pqueue.h"

typedef struct valve {
    char * name;
    int flow;
    int id;
    LIST * next;
} VALVE;

typedef struct dist {
    VALVE * valve;
    int d;
} DIST;

typedef struct loc {
    VALVE * val;
    int length;
} LOC;

static int loccmp (LOC * a, LOC * b) {
    return a->length-b->length;
}

static int compare(VALVE * a, VALVE * b) {
    return strcmp(a->name, b->name);
}

static unsigned hash(VALVE * v) {
    return v->name[0]+v->name[1];
}

VALVE * createValve(SET * store, char name[3]) {
    VALVE * add = malloc(sizeof(VALVE));
    add->name = name;
    VALVE * found = findElement(store, add);
    if (found != NULL) {
        return found;
    }
    add->next = createList(NULL);
    add->id = numElements(store);
    addElement(store, add);
    return add;
}

bool * duplicate(bool * state, int num, int id) {
    bool * out = malloc(num*sizeof(bool));
    memcpy(out, state, num*sizeof(bool));
    out[id] = true;
    return out;
}

int trace(VALVE * cur, bool * state, int step, int num, int *** hash) {
    if (step <= 0 || state[cur->id]) {
        return 0;
    }
    int hashVal = 0;
    for (int i = 0; i < num; i++) {
        hashVal *= 2;
        hashVal += state[i];
    }
    if (hash[step-1][cur->id][hashVal] != -1) {
        return hash[step-1][cur->id][hashVal];
    }
    
    int max = 0;
    for (int i = 0; i < numItems(cur->next); i++) {
        DIST * temp = removeFirst(cur->next);
        int val = cur->flow*(step-1) + trace(temp->valve, duplicate(state, num, cur->id), step-!!cur->flow-temp->d, num, hash);
        if (val > max) {
            max = val;
        }
        addLast(cur->next, temp);
    }
    hash[step-1][cur->id][hashVal] = max;
    return max;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    SET * store = createSet(676, compare, hash);
    VALVE * aa;
    while(fgets(line, sizeof(line), fp)) {
        char * name = calloc(3, sizeof(char));
        name[0] = line[6];
        name[1] = line[7];
        VALVE * cur = createValve(store, name);
        if (name[0] == 'A' && name[1] == 'A') {
            aa = cur;
        }
        cur->flow = atoi(strtok(line+23, "; tunnels lead to valves "));
        char * tok = strtok(NULL, "; tunnels lead to valves ");
        while (tok) {
            char * temp = calloc(3, sizeof(char));
            temp[0] = tok[0];
            temp[1] = tok[1];
            addLast(cur->next, createValve(store, temp));
            tok = strtok(NULL, ", ");
        }
    }

    SET * jumps = createSet(676, compare, hash);
    VALVE ** valves = getElements(store);
    for (int i = 0; i < numElements(store); i++) {
        if (valves[i]->flow || valves[i] == aa) {
            VALVE * jump = createValve(jumps, valves[i]->name);
            jump->flow = valves[i]->flow;
            for (int j = i+1; j < numElements(store); j++) {
                if (i != j && valves[j]->flow) {
                    int * dist = malloc(numElements(store)*sizeof(int));
                    for (int k = 0; k < numElements(store); k++) {
                        dist[k] = INT_MAX;
                    }
                    dist[valves[i]->id] = 0;
                    PQ * queue = createQueue(loccmp);
                    LOC * cur = malloc(sizeof(LOC));
                    cur->length = 0;
                    cur->val = valves[i];
                    addEntry(queue, cur);
                    while(cur->val != valves[j]) {
                        for (int k = 0; k < numItems(cur->val->next); k++) {
                            LOC * add = malloc(sizeof(LOC));
                            add->length = cur->length+1;
                            add->val = removeFirst(cur->val->next);
                            addEntry(queue, add);
                            addLast(cur->val->next, add->val);
                        }

                        do {
                            cur = removeEntry(queue);
                        } while(dist[cur->val->id] <= cur->length);
                        dist[cur->val->id] = cur->length;
                    }
                    DIST * d = malloc(sizeof(DIST));
                    d->d = cur->length;
                    d->valve = createValve(jumps, valves[j]->name);
                    addLast(jump->next, d);
                    if (valves[i] != aa) {
                        DIST * b = malloc(sizeof(DIST));
                        b->d = cur->length;
                        b->valve = jump;
                        addLast(d->valve->next, b);
                    }
                }
            }
            if (valves[i] == aa) {
                aa = jump;
            }
        }
    }

    int *** hash = malloc(30*sizeof(int **));
    for (int i = 0; i < 30; i++) {
        hash[i] = malloc(numElements(jumps)*sizeof(int *));
        for (int j = 0; j < numElements(jumps); j++) {
            hash[i][j] = malloc(pow(2, numElements(jumps))*sizeof(int));
            for (int k = 0; k < pow(2, numElements(jumps)); k++) {
                hash[i][j][k] = -1;
            }
        }
    }
    printf("%d\n", trace(aa, calloc(numElements(jumps), sizeof(bool)), 30, numElements(jumps), hash));
    return 0;
}