/* 
   Author: Itay Volk
   Date: 12/11/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    long long num;
    struct node * next;
} NODE;

long long numPlaces (long long n) {
    if (n < 10) return 1;
    return 1 + numPlaces (n / 10);
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char * buffer = malloc(length);
    fread(buffer, 1, length, fp);
    fclose(fp);

    NODE * head = malloc(sizeof(NODE));
    head->num = -1;
    head->next = NULL;
    NODE * last = head;

    char * tok = strtok(strtok(buffer, "\n"), " ");
    while (tok != NULL) {
        last->next = malloc(sizeof(NODE));
        last = last->next;
        last->next = NULL;
        last->num = (long long)atol(tok);
        tok = strtok(NULL, " ");
    }

    for (int i = 0; i < 25; i++) {
        printf("%d\n", i);
        last = head->next;
        while (last != NULL) {
            if (last->num == 0) {
                last->num = 1;
            } else if (numPlaces(last->num)%2 == 0) {
                NODE * temp = malloc(sizeof(NODE));
                temp->next = last->next;
                last->next = temp;
                temp->num = last->num % (long long)(pow(10, numPlaces(last->num)/2)+0.5);
                last->num /= (long long)(pow(10, numPlaces(last->num)/2)+0.5);
                last = temp;
            } else {
                last->num *= 2024;
            }
            last = last->next;
        }
    }
    
    int count = 0;
    head = head->next;
    while(head != NULL) {
        count++;
        head = head->next;
    }
    printf("%d\n", count);
    return 0;
}