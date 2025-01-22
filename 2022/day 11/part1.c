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
    int level;
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
            i->level = atoi(tok);
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

    for (int r = 0; r < 20; r++) {
        for (int i = 0; i < num; i++) {
            while (numItems(monkeys[i]->items)) {
                monkeys[i]->count++;
                ITEM * item = removeFirst(monkeys[i]->items);
                int num = monkeys[i]->num;
                if (!num) {
                    num = item->level;
                }
                if (monkeys[i]->op) {
                    item->level *= num;
                } else {
                    item->level += num;
                }
                item->level /= 3;
                if (item->level%monkeys[i]->test) {
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
    printf("%d\n", m1*m2);
    return 0;
}