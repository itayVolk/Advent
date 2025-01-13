/* 
   Author: Itay Volk
   Date: 01/12/2025
*/

#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];
    
    double ** pos = calloc(3, sizeof(double *));
    int ** vel = calloc(3, sizeof(int *));
    
    int num = 0;
    while (fgets(line, sizeof(line), fp) != NULL && num < 3) {
        pos[num] = calloc(3, sizeof(double));
        vel[num] = calloc(3, sizeof(int));
        pos[num][0] = atoll(strtok(line, ", "));
        pos[num][1] = atoll(strtok(NULL, ", "));
        pos[num][2] = atoll(strtok(NULL, ", "));
        vel[num][0] = atoi(strtok(NULL, " @ "));
        vel[num][1] = atoi(strtok(NULL, ", "));
        vel[num][2] = atoi(strtok(NULL, ", "));
        if (num > 0) {
            for (int i = 0; i < 3; i++) {
                pos[num][i] -= pos[0][i];
                vel[num][i] -= vel[0][i];
            }
        }
        num++;
    }

    long long t1 = round(-(((pos[1][1]*pos[2][2] - pos[1][2]*pos[2][1])*vel[2][0] - (pos[1][0]*pos[2][2] - pos[1][2]*pos[2][0])*vel[2][1] + (pos[1][0]*pos[2][1] - pos[1][1]*pos[2][0])*vel[2][2]))/
                ((vel[1][1]*pos[2][2] - vel[1][2]*pos[2][1])*vel[2][0] - (vel[1][0]*pos[2][2] - vel[1][2]*pos[2][0])*vel[2][1] + (vel[1][0]*pos[2][1] - vel[1][1]*pos[2][0])*vel[2][2]));
    long long t2 = round(-(((pos[1][1]*pos[2][2] - pos[1][2]*pos[2][1])*vel[1][0] - (pos[1][0]*pos[2][2] - pos[1][2]*pos[2][0])*vel[1][1] + (pos[1][0]*pos[2][1] - pos[1][1]*pos[2][0])*vel[1][2]))/
                ((pos[1][1]*vel[2][2] - pos[1][2]*vel[2][1])*vel[1][0] - (pos[1][0]*vel[2][2] - pos[1][2]*vel[2][0])*vel[1][1] + (pos[1][0]*vel[2][1] - pos[1][1]*vel[2][0])*vel[1][2]));
    long long out = 0;
    for (int i = 0; i < 3; i++) {
        long long c = pos[1][i]+pos[0][i] + t1*(vel[1][i]+vel[0][i]);
        out += c - t1*((pos[2][i]+pos[0][i] + t2*(vel[2][i]+vel[0][i]))-c)/(t2-t1);
    }
    printf("%lld\n", out);
    return 0;
}