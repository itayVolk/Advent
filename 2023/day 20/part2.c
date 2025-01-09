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

#define MAX 676

typedef struct wrap {
    int num;
} WRAP;

typedef struct module {
    bool inputs[MAX];
    int num;
    int type;
    LIST * out;
} MODULE;

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

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    MODULE ** modules = calloc(MAX, sizeof(MODULE *));
    while(fgets(line, sizeof(line), fp) != NULL) {
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
        modules[id]->out = createList(NULL);
        char * tok = strtok(line, ">");
        tok = strtok(NULL, ", ");
        while(tok != NULL) {
            WRAP * out = malloc(sizeof(WRAP));
            out->num = hash(tok);
            addLast(modules[id]->out, out);
            tok = strtok(NULL, ", ");
        }
    }

    int sender;
    for (int i = 0; i < MAX; i++) {
        if (modules[i] != NULL) {
            WRAP ** out = getItems(modules[i]->out);
            for (int j = 0; j < numItems(modules[i]->out); j++) {
                if (modules[out[j]->num] != NULL && modules[out[j]->num]->type == 1) {
                    modules[out[j]->num]->num++;
                } else if (out[j]->num == hash("rx")) {
                    sender = i;
                }
            }
        }
    }

    LIST * pulses = createList(NULL);
    PULSE * first = malloc(sizeof(PULSE));
    first->source = -1;
    first->target = hash("br");
    first->val = false;
    long long n = 0;
    long long * reached = calloc(modules[sender]->num, sizeof(long long));
    int size = 0;
    while (true) {
        n++;
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
                    WRAP ** targets = getItems(modules[sent->target]->out);
                    for (int i = 0; i < numItems(modules[sent->target]->out); i++) {
                        PULSE * p = malloc(sizeof(PULSE));
                        p->target = targets[i]->num;
                        p->source = sent->target;
                        p->val = send;
                        addLast(pulses, p);
                        if (p->target == sender && p->val) {
                            reached[size++] = n;
                            if (size == modules[sender]->num) {
                                long long lcm = reached[0];
                                for (int i = 1; i < size; i++) {
                                    lcm = lcm*reached[i]/gcd(lcm, reached[i]);
                                }
                                printf("%lld\n", lcm);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}