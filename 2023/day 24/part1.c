/* 
   Author: Itay Volk
   Date: 01/12/2025
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LOW 200000000000000
#define HIGH 400000000000000

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[512];

    double * slopes = calloc(500, sizeof(double));
    double * intercepts = calloc(500, sizeof(double));
    long long * x0 = calloc(500, sizeof(long long));
    int * vx = calloc(500, sizeof(int));
    int num = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        x0[num] = atoll(strtok(line, ", "));
        long long y = atoll(strtok(NULL, ", "));
        strtok(NULL, ", ");
        vx[num] = atoi(strtok(NULL, " @ "));
        int dy = atoi(strtok(NULL, ", "));
        slopes[num] = (double)(dy)/vx[num];
        intercepts[num] = y - slopes[num]*x0[num];
        num++;
    }

    int count = 0;
    for (int i = 0; i < num; i++) {
        for (int j = i+1; j < num; j++) {
            double x = (intercepts[j] - intercepts[i])/(slopes[i] - slopes[j]);
            double y = slopes[i]*x + intercepts[i];
            double ta = (x-x0[i])/((double)vx[i]);
            double tb = (x-x0[j])/((double)vx[j]);
            if (LOW <= x && x <= HIGH && LOW <= y && y <= HIGH && ta > 0 && tb > 0) {
                count++;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}