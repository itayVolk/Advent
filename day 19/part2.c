/* 
   Author: Itay Volk
   Date: 12/18/2024
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct dict {
    char * string;
    long long options;
} DICT;

static int compare(DICT * a, DICT * b) {
    return strcmp(a->string, b->string);
}

char * getString(int pos, int len, char string[])
{
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

long long check(char ** available, int count, char * try, LIST * dict) {
    DICT * entry = entry = malloc(sizeof(DICT));
    entry->string = try;
    entry->options = -1;
    DICT * found = findItem(dict, entry);
    if (found != NULL) {
        return found->options;
    }
    long long num = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(try, available[i]) == 0) {
            num++;
        } else if (strlen(try) > strlen(available[i]) && strcmp(available[i], getString(0, strlen(available[i]), try)) == 0) {
            num += check(available, count, getString(strlen(available[i]), -1, try), dict);
        }
    }
    entry->options = num;
    addFirst(dict, entry);
    return num;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[3000];

    char ** available = malloc(500*sizeof(char*));
    fgets(line, sizeof(line), fp);
    int count = -1;
    char * tok = strtok(line, ", ");
    while(tok != NULL) {
        // printf("t%s\n", tok);
        available[++count] = malloc((strlen(tok)+1)*sizeof(char));
        strcpy(available[count], tok);
        if (available[count][strlen(available[count])-1] == '\n') {
            available[count][strlen(available[count])-1] = '\0';
        }
        tok = strtok(NULL, ", ");
    }
    count++;
    fgets(line, sizeof(line), fp);

    long long possible = 0;
    LIST * dict = createList(compare);

    while(fgets(line, sizeof(line), fp) != NULL) {
        possible += check(available, count, getString(0, strlen(line)-1, line), dict);
    }
    printf("%lld\n", possible);
    return 0;
}