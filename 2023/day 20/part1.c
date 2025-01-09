/* 
   Author: Itay Volk
   Date: 01/08/2025
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "table.h"

#define MAX 676
#define RANGE 1000

typedef struct wrap {
    int num;
} WRAP;

typedef struct module {
    bool inputs[MAX];
    int num;
    int type;
    LIST * out;
} MODULE;

typedef struct dict {
    bool modules[MAX];
    int n;
    long long sent[2];
} DICT;

typedef struct pulse {
    int source;
    int target;
    bool val;
} PULSE;

int hash(char * c) {
    if (!isalpha(c[1])) {
        return c[0]-'a';
    }
    return (c[0]-'a')*26 + c[1]-'a';
}

static int compare(DICT * a, DICT * b) {
    for (int i = 0; i < MAX; i++) {
        if (a->modules[i] != b->modules[i]) {
            return 1;
        }
    }
    return 0;
}

static unsigned hashDict(DICT * d) {
    int hash = 0;
    for (int i = 0; i < MAX; i++) {
        if (d->modules[i]) {
            hash++;
        }
    }
    return hash;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    MODULE ** modules = calloc(MAX, sizeof(MODULE *));
    while(fgets(line, sizeof(line), fp) != NULL) {
        // printf("%s", line);
        int id;
        if (!isalpha(line[0])) {
            id = hash(line+1);
        } else {
            id = hash(line);
        }
        modules[id] = malloc(sizeof(MODULE));
        modules[id]->num = 0;
        modules[id]->inputs[0] = false;
        if (!isalpha(line[0])) {
            modules[id]->type = line[0]=='&';
            if (modules[id]->type) {
                for (int i = 0; i < MAX; i++) {
                    modules[id]->inputs[i] = false;
                }
            }
        } else {
            modules[id]->type = -1;
        }
        // printf("%d %d\n", id, modules[id]->type);
        modules[id]->out = createList(NULL);
        char * tok = strtok(line, ">");
        tok = strtok(NULL, ", ");
        while(tok != NULL) {
            WRAP * out = malloc(sizeof(WRAP));
            out->num = hash(tok);
            // printf("%d, ", out->num);
            addLast(modules[id]->out, out);
            tok = strtok(NULL, ", ");
        }
        // printf("\n");
    }
    for (int i = 0; i < MAX; i++) {
        if (modules[i] != NULL) {
            WRAP ** out = getItems(modules[i]->out);
            for (int j = 0; j < numItems(modules[i]->out); j++) {
                if (modules[out[j]->num] != NULL && modules[out[j]->num]->type == 1) {
                    modules[out[j]->num]->num++;
                }
            }
        }
    }
    // printf("setup\n");
    SET * cash = createSet(1001, compare, hashDict);
    DICT * init = malloc(sizeof(DICT));
    init->n = 0;
    init->sent[0] = 0;
    init->sent[1] = 0;
    for (int i = 0; i < MAX; i++) {
        init->modules[i] = false;
    }
    addElement(cash, init);
    LIST * pulses = createList(NULL);
    PULSE * first = malloc(sizeof(PULSE));
    first->source = -1;
    first->target = hash("br");
    first->val = false;
    long long *types = calloc(2, sizeof(long long));
    for (int n = 0; n < RANGE; n++) {
        types[0]++;
        addFirst(pulses, first);
        while (numItems(pulses) > 0) {
            PULSE * sent = removeFirst(pulses);
            if (modules[sent->target] != NULL) {
                int send = -1;
                switch(modules[sent->target]->type) {
                    case 0:
                        if (!sent->val) {
                            modules[sent->target]->inputs[0] = !modules[sent->target]->inputs[0];
                            send = modules[sent->target]->inputs[0];
                        }
                        break;
                    case 1:
                        modules[sent->target]->inputs[sent->source] = sent->val;
                        int num = 0;
                        for (int i = 0; i < MAX; i++) {
                            if (modules[sent->target]->inputs[i] == 1)
                                num++;
                        }
                        send = num != modules[sent->target]->num;
                        break;
                    case -1:
                        send = sent->val;
                        break;
                }

                if (send != -1) {
                    types[send] += numItems(modules[sent->target]->out);
                    WRAP ** targets = getItems(modules[sent->target]->out);
                    for (int i = 0; i < numItems(modules[sent->target]->out); i++) {
                        PULSE * p = malloc(sizeof(PULSE));
                        p->target = targets[i]->num;
                        p->source = sent->target;
                        p->val = send;
                        addLast(pulses, p);
                    }
                }
            }
        }

        DICT * search = malloc(sizeof(DICT));
        for (int i = 0; i < MAX; i++) {
            if (modules[i] != NULL && modules[i]->type != -1) {
                if (modules[i]->type) {
                    search->modules[i] = false;
                    for (int j = 0; j < MAX; j++) {
                        if (modules[i]->inputs[j] == 1) {
                            search->modules[i] = true;
                            break;
                        }
                    }
                } else {
                    search->modules[i] = modules[i]->inputs[0];
                }
            } else {
                search->modules[i] = 0;
            }
        }

        DICT * found = findElement(cash, search);
        if (found != NULL) {
            int counts = (RANGE-(double)found->n)/(n-found->n+1)+0.5;
            long long low = 0;
            long long high = 0;
            int stop = found->n+(RANGE-found->n)%(n-found->n+1)-1;
            DICT ** elements = getElements(cash);
            for (int i = 0; i < numElements(cash); i++) {
                if (elements[i]->n == stop) {
                    low = elements[i]->sent[0];
                    high = elements[i]->sent[1];
                    break;
                }
            }
            low += counts*(types[0]-found->sent[0]);
            high += counts*(types[1]-found->sent[1]);
            printf("%lld\n", high*low);
            return 0;
        }
        search->n = n+1;
        search->sent[0] = types[0];
        search->sent[1] = types[1];
        addElement(cash, search);
    }
    printf("%lld\n", types[0]*types[1]);
    return 0;
}