/* 
   Author: Itay Volk
   Date: 01/07/2025
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "list.h"

typedef struct rule {
    char type;
    bool dir;
    int bound;
    int goal;
} RULE;

typedef struct range {
    int * start;
    int * end;
} RANGE;

#define MAX 17576

int hash(char * flow) {
    if (flow[0] == 'A') {
        return 0;
    }
    if (flow[0] == 'R') {
        return -1;
    }
    int hash = 0;
    for (int i = 0; i < strlen(flow) && isalpha(flow[i]); i++) {
        hash *= 26;
        hash += flow[i]-'a';
    } 
    return hash;
}

int char2int(char c) {
    switch (c) {
        case 'x':
            return 0;
        case 'm':
            return 1;
        case 'a':
            return 2;
        case 's':
            return 3;
    }
    return -1;
}

long long trace(RANGE * range, int cur, LIST ** flows) {
    if (cur == -1) {
        return 0;
    }
    if (cur == 0) {
        long long mult = 1;
        for (int i = 0; i < 4; i++) {
            mult *= range->end[i]-range->start[i]+1;
        }
        return mult;
    }

    long long out = 0;
    RULE ** rules = getItems(flows[cur]);
    for (int i = 0; i < numItems(flows[cur])-1; i++) {
        int index = char2int(rules[i]->type);
        if (range->start[index] <= rules[i]->bound && rules[i]->bound <= range->end[index]) {
            RANGE * in = malloc(sizeof(RANGE));
            in->start = malloc(4*sizeof(int));
            in->end = malloc(4*sizeof(int));
            if (rules[i]->dir) {
                in->start[index] = rules[i]->bound+1;
                in->end[index] = range->end[index];
                range->end[index] = rules[i]->bound;
            } else {
                in->start[index] = range->start[index];
                in->end[index] = rules[i]->bound-1;
                range->start[index] = rules[i]->bound;
            }
            for (int j = 0; j < 4; j++) {
                if (j != index) {
                    in->start[j] = range->start[j];
                    in->end[j] = range->end[j];
                }
            }
            out += trace(in, rules[i]->goal, flows);
        } else if ((rules[i]->bound < range->start[index]) == rules[i]->dir) {
            return out + trace(range, rules[i]->goal, flows);
        }
    }
    return out + trace(range, rules[numItems(flows[cur])-1]->goal, flows);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    LIST ** flows = malloc(MAX*sizeof(LIST *));
    while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
        char * ptr = NULL;
        int flow = hash(strtok_s(line, "{", &ptr));
        char * tok = strtok_s(NULL, ",", &ptr);
        flows[flow] = createList(NULL);
        while (tok != NULL) {
            RULE * rule = malloc(sizeof(RULE));
            if (tok[1] == '>' || tok[1] == '<') {
                rule->type = tok[0];
                rule->dir = tok[1]=='>';
                char * tokPtr = NULL;
                rule->bound = atoi(strtok_s(tok, ":", &tokPtr)+2);
                rule->goal = hash(strtok_s(NULL, ":", &tokPtr));
            } else {
                rule->type = '-';
                rule->dir = false;
                rule->bound = -1;
                rule->goal = hash(tok);
            }
            addLast(flows[flow], rule);
            tok = strtok_s(NULL, ",", &ptr);
        }
    }

    RANGE * add = malloc(sizeof(RANGE));
    int start[4] = {1, 1, 1, 1};
    add->start = start;
    int end[4] = {4000, 4000, 4000, 4000};
    add->end = end;
    printf("%lld\n", trace(add, hash("in"), flows));
    return 0;
}