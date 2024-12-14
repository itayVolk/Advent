/* 
   Author: Itay Volk
   Date: 12/13/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node {
    int x;
    int y;
    int vx;
    int vy;
    struct node * next;
} NODE;

#define HEIGHT 103
#define WIDTH 101

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

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    NODE * head = malloc(sizeof(NODE));
    head->x = -1;
    head->y = -1;
    head->vx = -1;
    head->vy = -1;
    head->next = NULL;
    NODE * last = head;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        last->next = malloc(sizeof(NODE));
        last = last->next;
        last->next = NULL;
        char *pos = strtok(line, " ");
        char *vel = strtok(NULL, " ");
        last->x = atoi(getString(2, -1, strtok(pos, ",")));
        last->y = atoi(strtok(NULL, ","));
        last->vx = atoi(getString(2, -1, strtok(vel, ",")));
        last->vy = atoi(strtok(NULL, ","));
    }

    for (int i = 0; i < 100; i++) {
        printf("%d\n", i);
        last = head->next;
        while (last != NULL) {
            last->x += last->vx;
            if (last->x < 0) {
                last->x += WIDTH;
            } else if (last->x >= WIDTH) {
                last->x -= WIDTH;
            }
            last->y += last->vy;
            if (last->y < 0) {
                last->y += HEIGHT;
            } else if (last->y >= HEIGHT) {
                last->y -= HEIGHT;
            }
            last = last->next;
        }
    }
    
    int quads[4];
    head = head->next;
    while(head != NULL) {
        printf("%d:%d\n", head->x, head->y);
        if (head->x != WIDTH/2 && head->y != HEIGHT/2) {
            int quad = 0;
            if (head->x > WIDTH/2) {
                quad += 2;
            }
            if (head->y > HEIGHT/2) {
                quad++;
            }
            quads[quad]++;
        }
        head = head->next;
    }
    int sum = 1;
    for (int i = 0; i < 4; i++) {
        printf("q%d:%d\n", i, quads[i]);
        sum *= quads[i];
    }
    printf("%d\n", sum);
    return 0;
}