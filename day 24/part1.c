/* 
   Author: Itay Volk
   Date: 12/23/2024
*/
//TODO Should be 51410244478064
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef enum {AND, OR, XOR} OPS;

typedef struct dict {
    int out;
    int a;
    int b;
    OPS op;
} DICT;

static int compare (DICT * a, int * search) {
    return a->out != *search;
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

#define HASH_MAX 12317
int hash(char * str) {
    if (str[0] >= 'x') {
        return (str[0]-'x')*50 + atoi(getString(1, 2, str));
    }
    return 150 + str[0]-'a' + (str[1]-'a')*23 + (str[2]-'a')*529;
}

void calc(int * out, bool a, bool b, OPS op) {
    switch (op) {
        case AND:
            *out = a&&b;
            return;
        case OR:
            *out = a||b;
            return;
        case XOR:
            *out = a!=b;
            return;
    }
}

bool compute(LIST * dict, int a, int b, int * wires) {
    if (wires[a] == -1) {
        DICT * match = findItem(dict, &a);
        if (match == NULL) {
            return false;
        } else {
            if (compute(dict, match->a, match->b, wires)) {
                calc(&wires[a], wires[match->a], wires[match->b], match->op);
                removeItem(dict, &match->out);
            }
        }
    }

    if (wires[b] == -1) {
        DICT * match = findItem(dict, &b);
        if (match == NULL) {
            return false;
        } else {
            if (compute(dict, match->a, match->b, wires)) {
                calc(&wires[b], wires[match->a], wires[match->b], match->op);
                removeItem(dict, &match->out);
            }
        }
    }
    return true;
}

OPS str2op(char * str) {
    if (strcmp(str, "AND") == 0) {
        return AND;
    }
    if (strcmp(str, "OR") == 0) {
        return OR;
    }
    return XOR;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int *wires = calloc(HASH_MAX, sizeof(int));
    for (int i = 0; i < HASH_MAX; i++) {
        wires[i] = -1;
    }
    while(fgets(line, sizeof(line), fp) != NULL && line[0] == 'x') {
        wires[hash(line)] = atoi(getString(5, 1, line));
    }
    do {
        wires[hash(line)] = atoi(getString(5, 1, line));
    } while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0);

    LIST * dict = createList(compare);
    while(fgets(line, sizeof(line), fp) != NULL) {
        int a = hash(strtok(line, " "));
        OPS op = str2op(strtok(NULL, " "));
        int b = hash(strtok(NULL, " "));
        strtok(NULL, " ");
        int out = hash(strtok(NULL, " "));
        if (compute(dict, a, b, wires)) {
            calc(&wires[out], wires[a], wires[b], op);
        } else {
            DICT * add = malloc(sizeof(DICT));
            add->out = out;
            add->a = a;
            add->b = b;
            add->op = op;
            addLast(dict, add);
        }
    }

    while(numItems(dict) > 0) {
        DICT * out = removeFirst(dict);
        if (compute(dict, out->a, out->b, wires)) {
            calc(&wires[out->out], wires[out->a], wires[out->b], out->op);
        } else {
            addLast(dict, out);
        }
    }

    long long sum = 0;
    for (int i = 149; i >= 100; i--) {
        if (wires[i] != -1) {
            sum *= 2;
            sum += wires[i];
        }
    }
    printf("%lld\n", sum);
    return 0;
}