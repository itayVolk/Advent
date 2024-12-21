/* 
   Author: Itay Volk
   Date: 12/19/2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

typedef struct dict {
    char move;
    int x;
    int y;
} DICT;

static int compare(DICT * a, DICT * b) {
    return a->move-b->move;
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

int trace(char prev, char cur, LIST * dict, LIST * dirs, int ***** cost, int depth) {
    if (depth == 3) {
        return 1;
    }

    DICT * search = malloc(sizeof(DICT));
    search->move = prev;
    DICT * prevLoc = findItem(dict, search);
    search->move = cur;
    DICT * loc = findItem(dict, search);
    if (cost[prevLoc->y][prevLoc->x][loc->y][loc->x][depth] != 0) {
        return cost[prevLoc->y][prevLoc->x][loc->y][loc->x][depth];
    }
    
    search->move = ' ';
    DICT * hole = findItem(dict, search);
    int dx = 0;
    if (hole->x != loc->x || hole->y != prevLoc->y) {
        char first = loc->x < prevLoc->x ? '<' : '>';
        if (loc->x != prevLoc->x) {
            dx = trace('A', first, dirs, dirs, cost, depth+1);
            dx += trace(first, first, dirs, dirs, cost, depth+1) * (abs(loc->x - prevLoc->x)-1);
        } else {
            first = 'A';
        }
        char second = loc->y < prevLoc->y ? '^' : 'v';
        if (loc->y != prevLoc->y) {
            dx += trace(first, second, dirs, dirs, cost, depth+1);
            dx += trace(second, second, dirs, dirs, cost, depth+1) * (abs(loc->y - prevLoc->y)-1);
        } else {
            second = first;
        }
        dx += trace(second, 'A', dirs, dirs, cost, depth+1);
    }

    if (hole->y != loc->y || hole->x != prevLoc->x) {
        char first = loc->y < prevLoc->y ? '^' : 'v';
        int dy = 0;
        if (loc->y != prevLoc->y) {
            dy = trace('A', first, dirs, dirs, cost, depth+1);
            dy += trace(first, first, dirs, dirs, cost, depth+1) * (abs(loc->y - prevLoc->y)-1);
        } else {
            first  = 'A';
        }
        char second = loc->x < prevLoc->x ? '<' : '>';
        if (loc->x != prevLoc->x) {
            dy += trace(first, second, dirs, dirs, cost, depth+1);
            dy += trace(second, second, dirs, dirs, cost, depth+1) * (abs(loc->x - prevLoc->x)-1);
        } else {
            second = first;
        }
        dy += trace(second, 'A', dirs, dirs, cost, depth+1);
        if (dx == 0 || dy < dx) {
            dx = dy;
        }
    }

    cost[prevLoc->y][prevLoc->x][loc->y][loc->x][depth] = dx;
    return dx;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    LIST * num = createList(compare);
    char chars[12] = {'7', '8', '9', '4', '5', '6', '1', '2', '3', ' ', '0', 'A'};
    for (int i = 0; i < 12; i++) {
        DICT * add = malloc(sizeof(DICT));
        add->move = chars[i];
        add->x = i%3;
        add->y = i/3;
        addFirst(num, add);
    }

    LIST * move = createList(compare);
    char dirs[6] = {' ', '^', 'A', '<', 'v', '>'};
    for (int i = 0; i < 6; i++) {
        DICT * add = malloc(sizeof(DICT));
        add->move = dirs[i];
        add->x = i%3;
        add->y = i/3;
        addFirst(move, add);
    }

    int ***** costs = malloc(4*sizeof(int *));
    for (int i = 0; i < 4; i++) {
        costs[i] = malloc(4*sizeof(int *));
        for (int j = 0; j < 4; j++) {
            costs[i][j] = malloc(4*sizeof(int *));
            for (int k = 0; k < 4; k++) {
                costs[i][j][k] = malloc(4*sizeof(int *));
                for (int l = 0; l < 4; l++) {
                    costs[i][j][k][l] = calloc(3, sizeof(int));
                }
            }
        }
    }

    int complexity = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        int code = atoi(getString(0, strlen(line)-2, line));
        char prev = 'A';
        int cost = 0;

        for (int i = 0; i < strlen(line)-1; i++) {
            cost += trace(prev, line[i], num, move, costs, 0);
            prev = line[i];
        }
        complexity += cost*code;
    }
    printf("%d\n", complexity);
    return 0;
}