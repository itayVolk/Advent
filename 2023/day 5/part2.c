/* 
   Author: Itay Volk
   Date: 12/27/2024
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct range {
    long long start;
    long long length;
} RANGE;

static int comp(void * a, void * b) {
    return 0;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    LIST * cur = createList(comp);
    fgets(line, sizeof(line), fp);
    char * seed = strtok(strstr(line, ":")+2, " ");
    while (seed != NULL) {
        RANGE * add = malloc(sizeof(RANGE));
        add->start = atoll(seed);
        add->length = atoll(strtok(NULL, " "));
        addFirst(cur, add);
        seed = strtok(NULL, " ");
    }

    fgets(line, sizeof(line), fp);
    while(fgets(line, sizeof(line), fp) != NULL) {
        long long ** maps = malloc(50*sizeof(long long *));
        int count = 0;
        while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
            maps[count] = malloc(3*sizeof(long long));
            maps[count][0] = atoll(strtok(line, " ")); //dest
            maps[count][1] = atoll(strtok(NULL, " ")); //source
            maps[count][2] = atoll(strtok(NULL, " ")); //length
            count++;
        }
        LIST * next = createList(comp);
        while (numItems(cur) > 0) {
            RANGE * temp = removeFirst(cur);
            for (int i = 0; i < count; i++) {
                if (temp->start >= maps[i][1]) {
                    if (temp->start+temp->length <= maps[i][1] + maps[i][2]) {
                        RANGE * add = malloc(sizeof(RANGE));
                        add->start = temp->start-maps[i][1]+maps[i][0];
                        add->length = temp->length;
                        addFirst(next, add);
                        temp->start = -1;
                        temp->length = -1;
                        break;
                    } else if (temp->start < maps[i][1] + maps[i][2]) {
                        RANGE * add = malloc(sizeof(RANGE));
                        add->start = temp->start-maps[i][1]+maps[i][0];
                        add->length = maps[i][1]+maps[i][2]-temp->start;
                        addFirst(next, add);
                        temp->start += add->length;
                        temp->length -= add->length;
                        i = -1;
                    }
                } else if (temp->start + temp->length > maps[i][1] && temp->start + temp->length <= maps[i][1] + maps[i][2]) {
                    RANGE * add = malloc(sizeof(RANGE));
                    add->start = maps[i][0];
                    add->length = temp->start+temp->length-maps[i][1];
                    addFirst(next, add);
                    temp->length = maps[i][1]-temp->start;
                    i = -1;
                }
            }
            if (temp->start != -1) {
                addFirst(next, temp);
            } else {
                free(temp);
            }
        }
        destroyList(cur);
        cur = next;
    }

    long long min = LONG_LONG_MAX;
    while (numItems(cur) > 0) {
        long long temp = ((RANGE *)removeFirst(cur))->start;
        if (temp < min) {
            min = temp;
        }
    }
    printf("%lld\n", min);
    return 0;
}