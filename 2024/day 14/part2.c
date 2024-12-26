/* 
   Author: Itay Volk
   Date: 12/13/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

    bool unique = false;
    int count = 0;
    while (!unique) {
        count++;
        last = head->next;
        unique = true;
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
            if (unique) {
                NODE * inner = head->next;
                while (inner != last && unique) {
                    if (inner->x == last->x && inner->y==last->y) {
                        unique = false;
                    }
                    inner = inner->next;
                }
            }
            last = last->next;
        }
    }
    
    head = head->next;
    bool **points = malloc(HEIGHT*sizeof(bool*));
    for (int i = 0; i < HEIGHT; i++) {
        points[i] = calloc(WIDTH, sizeof(bool));
    }
    while(head != NULL) {
        points[head->y][head->x] = true;
        head = head->next;
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (points[i][j])
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("%d\n", count);
    return 0;
}