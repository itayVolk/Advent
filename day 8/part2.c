/* 
   Author: Itay Volk
   Date: 12/09/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    int x;
    int y;
    struct node * next;
} NODE;

typedef struct list {
    NODE * start;
    NODE * end;
} LIST;

#define RANGE 63

bool contains(LIST *lp, int x, int y) {
    NODE * cur = lp->start->next;
    while (cur != NULL) {
        if (cur->x == x && cur->y == y) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

int hash(char c) {
    if (c=='#') {
        return 0;
    }
    if ('0' <= c && c <= '9') {
        return c-'0'+1;
    }
    if ('a' <= c && c <= 'z') {
        return c-'a'+11;
    }
    return c-'A'+37;
}

bool antiCheck(LIST *nodes, int xp, int yp) {
    if (!contains(nodes, xp, yp)) {
        nodes->end->next = malloc(sizeof(NODE));
        nodes->end = nodes->end->next;
        nodes->end->x = xp;
        nodes->end->y = yp;
        nodes->end->next = NULL;
        return true;
    }
    return false;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    LIST ** antenas = malloc(RANGE*sizeof(LIST *));
    for (int i = 0; i < RANGE; i++) {
        antenas[i] = malloc(sizeof(LIST));
        antenas[i]->start = malloc(sizeof(NODE));
        antenas[i]->start->x = -1;
        antenas[i]->start->y = -1;
        antenas[i]->start->next = NULL;
        antenas[i]->end = antenas[i]->start;
    }

    int y = 0;
    while(fgets(line, sizeof(line), fp) != NULL && strcmp(line, "\n") != 0) {
        for (int x = 0; x < strlen(line)-1; x++) {
            if (line[x] != '.') {
                int i = hash(line[x]);
                antenas[i]->end->next = malloc(sizeof(NODE));
                antenas[i]->end = antenas[i]->end->next;
                antenas[i]->end->x = x;
                antenas[i]->end->y = y;
                antenas[i]->end->next = NULL;
            }
        }
        y++;
    }

    int count = 0;
    for (int i = 1; i < RANGE; i++) {
        // printf("%d\n", i);
        NODE * start = antenas[i]->start->next;
        while (start != NULL && start->next != NULL) {
            // printf("s%p\n", start);
            NODE * end = start->next;
            while (end != NULL) {
                // printf("e%p\n", end);
                int dx = end->x - start->x;
                int dy = end->y - start->y;
                int px = start->x;
                int py = start->y;
                while (px >= 0 && px < strlen(line)-1 && py >= 0 && py < y) {
                    if (antiCheck(antenas[0], px, py)) {
                        count++;
                    }
                    px += dx;
                    py += dy;
                }
                px = start->x;
                py = start->y;
                while (px >= 0 && px < strlen(line)-1 && py >= 0 && py < y) {
                    if (antiCheck(antenas[0], px, py)) {
                        count++;
                    }
                    px -= dx;
                    py -= dy;
                }
                end = end->next;
            }
            start = start->next;
        }
    }

    printf("%d\n", count);
    return 0;
}