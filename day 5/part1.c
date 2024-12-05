/* 
   Author: Itay Volk
   Date: 12/04/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int num;
    struct node * next;
} NODE;

typedef struct list {
    NODE * start;
    NODE * end;
} LIST;

#define RANGE 90

char * getString(int pos, int len, char string[])
{
    char * substring = calloc(len+1, sizeof(char));
    int i = 0;
    while (i < len) {
        substring[i] = string[pos + i];
        i++;
    }
    return substring;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    LIST ** order = malloc(RANGE*sizeof(LIST *));
    for (int i = 0; i < RANGE; i++) {
        order[i] = malloc(sizeof(LIST));
        order[i]->start = malloc(sizeof(NODE));
        order[i]->start->num = -1;
        order[i]->start->next = NULL;
        order[i]->end = order[i]->start;
    }

    while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
        int i = atoi(getString(0, 2, line))-10;
        order[i]->end->next = malloc(sizeof(NODE));
        order[i]->end = order[i]->end->next;
        order[i]->end->num = atoi(getString(3, 2, line));
    }

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int arr[30];
        char * token = strtok(line, ",");
        int l = 0;
        while (token != NULL) {
            arr[l++] = atoi(token);
            token = strtok(NULL, ",");
        }
        bool passes = true;
        for (int i = 1; i < l; i++) {
            for (int j = 0; j < i; j++) {
                NODE * cur = order[arr[i]-10]->start->next;
                while (cur != NULL && cur->num != arr[j]) {
                    cur = cur->next;
                }
                if (cur != NULL) {
                    passes = false;
                    break;
                }
            }
            if (!passes) {
                break;
            }
        }
        if (passes) {
            sum += arr[l/2];
        }
    }

    printf("%d\n", sum);
    return 0;
}