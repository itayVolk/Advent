/* 
   Author: Itay Volk
   Date: 01/23/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct range {
    int s;
    int e;
} RANGE;

#define SIZE 4000000

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    LIST ** map = malloc(SIZE*sizeof(LIST *));
    for (int i = 0; i < SIZE; i++) {
        map[i] = createList(NULL);
    }
    // int l = 0;
    while(fgets(line, sizeof(line), fp)) {
        int sx = atoi(strtok(line+12, ", y="));
        int sy = atoi(strtok(NULL, ", y="));
        int ex = atoi(strtok(NULL, ": closest beacon is at x="));
        int ey = atoi(strtok(NULL, ", y="));
        int d = abs(ex-sx) + abs(ey-sy);
        for (int i = -d; i <= d && sy+i < SIZE; i++) {
            if (sy+i < 0) {
                i = -sy-1;
            } else {
                int s = sx - (d-abs(i));
                if (s < 0) {
                    s = 0;
                }
                int e = sx + (d-abs(i));
                if (e >= SIZE) {
                    e = SIZE-1;
                }
                for (int j = 0; j < numItems(map[sy+i]); j++) {
                    RANGE * cur = removeFirst(map[sy+i]);
                    if (s <= cur->s && cur->e <= e) {
                        j--;
                        continue;
                    }
                    if (cur->s-1 <= e && e <= cur->e) {
                        e = cur->e;
                        j = -1;
                    }
                    if (cur->s <= s && s <= cur->e+1) {
                        s = cur->s;
                        j = -1;
                    }
                    if (j >= 0) {
                        addLast(map[sy+i], cur);
                    }
                }
                RANGE * add = malloc(sizeof(RANGE));
                add->s = s;
                add->e = e;
                addLast(map[sy+i], add);
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (numItems(map[i]) >= 2){
            RANGE * temp = removeFirst(map[i]);
            long long x = temp->s-1;
            if (x == -1) {
                x = temp->e+1;
            }
            printf("%lld\n", i+4000000*x);
            break;
        }
    }
    return 0;
}