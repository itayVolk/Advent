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

static int compare(RULE * r, int * part) {
    // if (r->type == '-') {
    //     return 0;
    // }
    int i;
    switch (r->type) {
        case 'x':
            i = 0;
            break;
        case 'm':
            i = 1;
            break;
        case 'a':
            i = 2;
            break;
        case 's':
            i = 3;
            break;
    }
    // printf("%c %d %d %d %d\n", r->type, r->bound, r->dir, r->goal, part[i]);
    return part[i] == r->bound || (part[i] < r->bound == r->dir);
}

bool trace(int * part, LIST * cur, LIST ** flows) {
    RULE * match = findItem(cur, part);
    if (match == NULL) {
        match = getLast(cur);
    }
    int next = match->goal;
    if (next <= 0) {
        // printf("%d, %c\n", next, match->type);
        return next+1;
    }
    // printf("%d:%d\n", next, numItems(flows[next]));
    return trace(part, flows[next], flows);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    LIST ** flows = malloc(MAX*sizeof(LIST *));
    while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
        char * ptr = NULL;
        // printf("line:%s\n", line);
        int flow = hash(strtok_s(line, "{", &ptr));
        char * tok = strtok_s(NULL, ",", &ptr);
        flows[flow] = createList(compare);
        while (tok != NULL) {
            // printf("%s\n", tok);
            RULE * rule = malloc(sizeof(RULE));
            if (tok[1] == '>' || tok[1] == '<') {
                // printf("in\n");
                rule->type = tok[0];
                rule->dir = tok[1]=='>';
                char * tokPtr = NULL;
                rule->bound = atoi(strtok_s(tok, ":", &tokPtr)+2);
                // printf("%d\n", rule->bound);
                rule->goal = hash(strtok_s(NULL, ":", &tokPtr));
            } else {
                rule->type = '-';
                rule->dir = false;
                rule->bound = -1;
                rule->goal = hash(tok);
            }
            // printf("%c %d %d %d\n", rule->type, rule->dir, rule->bound, rule->goal);
            addLast(flows[flow], rule);
            tok = strtok_s(NULL, ",", &ptr);
        }
    }

    long long sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        // printf("%s", line);
        int * part = malloc(4*sizeof(int));
        char * ptr = NULL;
        char * tok = strtok_s(line+1, ",", &ptr);
        long long inside = 0;
        for (int i = 0; i < 4; i++) {
            part[i] = atoi(tok+2);
            inside += part[i];
            tok = strtok_s(NULL, ",", &ptr);
        }
        if (trace(part, flows[hash("in")], flows)) {
            // printf("in\n");
            sum += inside;
        }
    }
    printf("%lld\n", sum);
    return 0;
}