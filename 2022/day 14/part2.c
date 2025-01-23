/* 
   Author: Itay Volk
   Date: 01/22/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HEIGHT 400
#define WIDTH 1000

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    bool ** map = malloc(HEIGHT*sizeof(bool *));
    for (int i = 0; i < HEIGHT; i++) {
        map[i] = calloc(WIDTH, sizeof(bool));
    }
    int my = 0;
    while(fgets(line, sizeof(line), fp)) {
        char * ptr = line;
        char * cur = strtok_s(line, " -> ", &ptr);
        char * ptr2 = cur;
        int sx = atoi(strtok_s(cur, ",", &ptr2));
        int sy = atoi(strtok_s(NULL, ",", &ptr2));
        if (sy > my) {
            my = sy;
        }
        cur = strtok_s(NULL, " -> ", &ptr);
        while (cur != NULL) {
            ptr2 = cur;
            int ex = atoi(strtok_s(cur, ",", &ptr2));
            int ey = atoi(strtok_s(NULL, ",", &ptr2));
            if (ey > my) {
                my = ey;
            }
            while (sx != ex || sy != ey) {
                map[sy][sx] = true;
                if (sx != ex) {
                    sx -= abs(sx-ex)/(sx-ex);
                } else {
                    sy -= abs(sy-ey)/(sy-ey);
                }
            }
            cur = strtok_s(NULL, " -> ", &ptr);
        }
        map[sy][sx] = true;
    }
    
    int num = 0;
    int y = 0;
    do {
        int x = 500;
        y = 0;
        while(y < my+2) {
            if (map[y][x] && map[y][--x]) {
                x += 2;
                if (map[y][x]) {
                    x--;
                    break;
                }
            }
            y++;
        }
        y--;
        map[y][x] = true;
        num++;
    } while(y > 0);
    printf("%d\n", num);
    return 0;
}