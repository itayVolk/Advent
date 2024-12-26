/* 
   Author: Itay Volk
   Date: 12/24/2024
*/

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

static int compare (DICT * a, DICT * search) {
    return search->out != a->a && search->out != a->b;
}

static int same (DICT * a, int * search) {
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

char *  unhash(int hash) {
    char * out = calloc(4, sizeof(char));
    out[3] = '\0';
    if (hash < 150) {
        out[0] = 'x' + hash/50;
        sprintf(out+1, "%d", hash%50);
    } else {
        hash -= 150;
        for (int i = 0; i < 3; i++) {
            out[i] = hash%23+'a';
            hash /= 23;
        }
    }
    return out;
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
        } else if (compute(dict, match->a, match->b, wires)) {
            calc(&wires[a], wires[match->a], wires[match->b], match->op);
            removeItem(dict, &match->out);
        } else {
            return false;
        }
    }

    if (wires[b] == -1) {
        DICT * match = findItem(dict, &b);
        if (match == NULL) {
            return false;
        } else if (compute(dict, match->a, match->b, wires)) {
            calc(&wires[b], wires[match->a], wires[match->b], match->op);
            removeItem(dict, &match->out);
        } else {
            return false;
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

char * op2str(OPS op) {
    switch (op) {
        case AND:
            return "AND";
        case OR:
            return "OR";
        case XOR:
            return "XOR";
    }
    return NULL;
}

DICT * findZ(DICT * out, LIST * gates) {
    if (out->out < 150) {
        return out;
    }
    // printf("%d\n", out->out);
    DICT * min = NULL;
    DICT ** arr = getItems(gates);
    for (int i = 0; i < numItems(gates); i++) {
        if ((arr[i]->a == out->out || arr[i]->b == out->out)) {
            DICT * temp = findZ(arr[i], gates);
            if (temp != NULL && (min == NULL || min->out > temp->out)) {
                min = temp;
            }
        }
    }
    return min;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    int *wires = calloc(HASH_MAX, sizeof(int));
    for (int i = 0; i < HASH_MAX; i++) {
        wires[i] = -1;
    }
    int count = 0;
    while(fgets(line, sizeof(line), fp) != NULL && line[0] == 'x') {
        wires[hash(line)] = atoi(getString(5, 1, line));
        count++;
    }
    do {
        wires[hash(line)] = atoi(getString(5, 1, line));
    } while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0);

    LIST * dict = createList(compare);
    LIST * ident = createList(same);
    while(fgets(line, sizeof(line), fp) != NULL) {
        int a = hash(strtok(line, " "));
        OPS op = str2op(strtok(NULL, " "));
        int b = hash(strtok(NULL, " "));
        strtok(NULL, " ");
        int out = hash(strtok(NULL, " "));
        DICT * add = malloc(sizeof(DICT));
        add->out = out;
        add->a = a;
        add->b = b;
        add->op = op;
        addLast(dict, add);
        addLast(ident, add);
    }

    char * out[8];
    int numOut = 0;

    DICT ** arr = getItems(dict);
    LIST * flags = createList(compare);
    LIST * copy = createList(same);
    for (int i = 0; i < numItems(dict); i++) {
        addFirst(copy, arr[i]);
        if (arr[i]->out < 150) {
            if (arr[i]->out != 100+count && arr[i]->op != XOR) {
                addFirst(flags, arr[i]);
            }
        } else if (arr[i]->a >= 100 && arr[i]->b >= 100 && arr[i]->op == XOR){
            addFirst(flags, arr[i]);
        }
    }
    while (numItems(flags) > 0) {
        DICT * first = removeFirst(flags);
        if (first->op == XOR) {
            int z = findZ(first, dict)->out-1;
            DICT * temp = findItem(ident, &z);
            out[numOut++] = unhash(first->out);
            out[numOut++] = unhash(temp->out);
            int swap = temp->out;
            temp->out = first->out;
            first->out = swap;
        }
    }

    while(numItems(copy) > 0) {
        DICT * out = removeFirst(copy);
        if (compute(copy, out->a, out->b, wires)) {
            calc(&wires[out->out], wires[out->a], wires[out->b], out->op);
        } else {
            addLast(copy, out);
        }
    }

    long long a = 0;
    long long b = 0;
    for (int i = 50; i >= 0; i--) {
        if (wires[i] != -1) {
            a *= 2;
            b *= 2;
            a += wires[i];
            b += wires[i+50];
        }
    }
    long long sum = 0;
    for (int i = 149; i >= 100; i--) {
        if (wires[i] != -1) {
            sum *= 2;
            sum += wires[i];
        }
    }

    long long dif = (a+b)^sum;
    count = 0;
    while (dif%2 == 0) {
        count++;
        dif /= 2;
    }
    
    while (numItems(dict) > 0) {
        DICT * temp = removeFirst(dict);
        if (temp->a < 100 && temp->b < 100 && temp->a%50 == count) {
            printf("%s\n", unhash(temp->out));
            out[numOut++] = unhash(temp->out);
        }
    }

    bool * sent = calloc(numOut, sizeof(bool));
    for (int i = 0; i < numOut; i++) {
        int min = -1;
        for (int j = 0; j < numOut; j++) {
            if (!sent[j] && (min == -1 || strcmp(out[min],out[j]) > 0)) {
                min = j;
            }
        }
        sent[min] = true;
        printf("%s,", out[min]);
    }
    return 0;
}