/* 
   Author: Itay Volk
   Date: 01/22/2025
*/

// #include <corecrt_memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
#include "pqueue.h"

typedef union value {
    LIST * list;
    int num;
} VALUE;

typedef struct item {
    bool type;
    struct item * parent;
    VALUE value;
} ITEM;

ITEM * createItem(char * line) {
    ITEM * cur = malloc(sizeof(ITEM));
    cur->type = true;
    cur->parent = NULL;
    cur->value.list = createList(NULL);
    ITEM * out = cur;
    for (int i = 1; i < strlen(line)-1; i++) {
        if (line[i] == '[') {
            ITEM * temp = malloc(sizeof(ITEM));
            temp->parent = cur;
            temp->type = true;
            temp->value.list = createList(NULL);
            cur = temp;
        } else if (line[i] == ']' || line[i] == ',') {
            if (cur->parent != NULL){
                addLast(cur->parent->value.list, cur);
                cur = cur->parent;
            }
        } else {
            if (cur->type) {
                ITEM * temp = malloc(sizeof(ITEM));
                temp->parent = cur;
                temp->type = false;
                temp->value.num = 0;
                cur = temp;
            }
            cur->value.num *= 10;
            cur->value.num += line[i]-'0';
        }
    }
    return out;
}

static int compare(ITEM * a, ITEM * b) {
    if (a->type && b->type) {
        ITEM ** arrA = getItems(a->value.list);
        ITEM ** arrB = getItems(b->value.list);
        for (int i = 0; i < numItems(a->value.list) && i < numItems(b->value.list); i++) {
            int temp = compare(arrA[i], arrB[i]);
            if (temp) {
                return temp;
            }
        }
        if (numItems(a->value.list) == numItems(b->value.list)) {
            return 0;
        }
        return 1-(numItems(a->value.list) < numItems(b->value.list))*2;
    }
    if (!a->type && !b->type) {
        if (a->value.num == b->value.num) {
            return 0;
        }
        return 1-(a->value.num < b->value.num)*2;
    }
    if (!a->type) {
        ITEM * cmpr = malloc(sizeof(ITEM));
        cmpr->type = true;
        cmpr->value.list = createList(NULL);
        addLast(cmpr->value.list, a);
        return compare(cmpr, b);
    }
    ITEM * cmpr = malloc(sizeof(ITEM));
    cmpr->type = true;
    cmpr->value.list = createList(NULL);
    addLast(cmpr->value.list, b);
    return compare(a, cmpr);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    PQ * queue = createQueue(compare);
    ITEM * divA = createItem("[[2]]\n");
    addEntry(queue, divA);
    ITEM * divB = createItem("[[6]]\n");
    addEntry(queue, divB);
    while(fgets(line, sizeof(line), fp)) {
        addEntry(queue, createItem(line));
        fgets(line, sizeof(line), fp);
        addEntry(queue, createItem(line));
        fgets(line, sizeof(line), fp);
    }

    int first;
    for (int i = 1; numEntries(queue) > 0; i++) {
        ITEM * temp = removeEntry(queue);
        if (temp == divA) {
            first = i;
        } else if (temp == divB) {
            printf("%d\n", i*first);
            return 0;
        }
    }
    return 0;
}