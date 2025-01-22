/* 
   Author: Itay Volk
   Date: 01/21/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

typedef struct monkey {
    int count;
    LIST * items;
    bool op;
    int num;
    int test;
    int t;
    int f;
} MONKEY;

typedef struct item {
    int diff[10];
} ITEM;

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    MONKEY * monkeys[10];
    int num = 0;
    while(fgets(line, sizeof(line), fp)) {
        monkeys[num] = malloc(sizeof(MONKEY));
        monkeys[num]->count = 0;
        monkeys[num]->items = createList(NULL);
        fgets(line, sizeof(line), fp);
        char * tok = strtok(line+18, ", ");
        while(tok != NULL) {
            ITEM * i = malloc(sizeof(ITEM));
            for (int l = 0; l < 10; l++) {
                i->diff[l] = atoi(tok);
            }
            addLast(monkeys[num]->items, i);
            tok = strtok(NULL, ", ");
        }
        fgets(line, sizeof(line), fp);
        monkeys[num]->op = line[23]=='*';
        monkeys[num]->num = line[25]=='o'?0:atoi(line+25);
        fgets(line, sizeof(line), fp);
        monkeys[num]->test = atoi(line+21);
        fgets(line, sizeof(line), fp);
        monkeys[num]->t = atoi(line+29);
        fgets(line, sizeof(line), fp);
        monkeys[num]->f = atoi(line+30);
        fgets(line, sizeof(line), fp);
        num++;
    }
    for (int i = 0; i < num; i++) {
        ITEM ** items = getItems(monkeys[i]->items);
        for (int j = 0; j < numItems(monkeys[i]->items); j++) {
            for (int k = 0; k < num; k++) {
                items[j]->diff[k] = (monkeys[k]->test-(items[j]->diff[k]%monkeys[k]->test))%monkeys[k]->test;
            }
        }
    }

    for (int r = 0; r < 10000; r++) {
        for (int i = 0; i < num; i++) {
            while (numItems(monkeys[i]->items)) {
                monkeys[i]->count++;
                ITEM * item = removeFirst(monkeys[i]->items);
                int cur = monkeys[i]->num;
                if (monkeys[i]->op) {
                    if (!cur) {
                        for (int j = 0; j < num; j++) {
                            item->diff[j] *= item->diff[j];
                            item->diff[j] %= monkeys[j]->test;
                            item->diff[j] = monkeys[j]->test - item->diff[j];
                            item->diff[j] %= monkeys[j]->test;
                        }
                    } else {
                        for (int j = 0; j < num; j++) {
                            item->diff[j] *= cur;
                            item->diff[j] %= monkeys[j]->test;
                        }
                    }
                } else {
                    for (int j = 0; j < num; j++) {
                        if (!cur) {
                            item->diff[j] -= item->diff[j];
                        } else {
                            item->diff[j] -= cur;
                        }
                        while(item->diff[j] < 0) {
                            item->diff[j] += monkeys[j]->test;
                        }
                    }
                }
                if (item->diff[i]) {
                    addLast(monkeys[monkeys[i]->f]->items, item);
                } else {
                    addLast(monkeys[monkeys[i]->t]->items, item);
                }
            }
        }
    }

    int m1 = 0;
    int m2 = 0;
    for (int i = 0; i < num; i++) {
        if (monkeys[i]->count > m1) {
            m2 = m1;
            m1 = monkeys[i]->count;
        } else if (monkeys[i]->count > m2) {
            m2 = monkeys[i]->count;
        }
    }
    printf("%lld\n", (long long)m1*m2);
    return 0;
}