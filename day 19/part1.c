/* 
   Author: Itay Volk
   Date: 12/18/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

bool check(char ** available, int count, char * try) {
    for (int i = 0; i < count; i++) {
        if (strcmp(try, available[i]) == 0 || (strlen(try) > strlen(available[i]) && strcmp(available[i], getString(0, strlen(available[i]), try)) == 0 && check(available, count, getString(strlen(available[i]), -1, try)))) {
            return true;
        }
    }

    return false;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[3000];

    char ** available = malloc(500*sizeof(char*));
    fgets(line, sizeof(line), fp);
    int count = -1;
    char * tok = strtok(line, ", ");
    while(tok != NULL) {
        available[++count] = malloc((strlen(tok)+1)*sizeof(char));
        strcpy(available[count], tok);
        if (available[count][strlen(available[count])-1] == '\n') {
            available[count][strlen(available[count])-1] = '\0';
        }
        tok = strtok(NULL, ", ");
    }
    fgets(line, sizeof(line), fp);

    int possible = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if (check(available, count, getString(0, strlen(line)-1, line))) {
            possible++;
        }
    }
    printf("%d\n", possible);
    return 0;
}