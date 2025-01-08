/* 
   Author: Itay Volk
   Date: 01/07/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct edge {
    long long sx;
    long long sy;
    long long ex;
    long long ey;
} EDGE;

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];
    LIST * edges = createList(NULL);

    long long x = 0;
    long long y = 0;
    long long count = 0;
    while(fgets(line, sizeof(line), fp) != NULL) {
        char end = line[strlen(line)-3];
        char * ptr = line;
        strtok_s(line, "#", &ptr);
        long dist = strtol(strtok_s(NULL, "#", &ptr), NULL, 16)/16;
        count += dist;
        EDGE * add = malloc(sizeof(EDGE));
        add->sx = x;
        add->sy = y;
        add->ex = x;
        add->ey = y;
        switch(end) {
            case '3': //U
                    add->ey -= dist;
                break;
            case '1': //D
                    add->ey += dist;
                break;
            case '2': //L
                    add->ex -= dist;
                break;
            case '0': //R
                    add->ex += dist;
                break;
        }
        x = add->ex;
        y = add->ey;
        addLast(edges, add);
    }

    long long area = 0;
    while (numItems(edges) > 0) {
        EDGE * e = removeFirst(edges);
        area += e->sx*e->ey-e->ex*e->sy;
    }
    printf("%lld\n", count/2+area/2+1);
    return 0;
}