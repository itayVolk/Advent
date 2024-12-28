/* 
   Author: Itay Volk
   Date: 12/28/2024
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE * fp = fopen("input.txt", "r");
    char *time = calloc(256, sizeof(char));
    char *dist = calloc(256, sizeof(char));
    fgets(time, 256, fp);
    fgets(dist, 256, fp);
    char * timePtr = time;
    char * distPtr = dist;
    time = strtok_s(time, " ", &timePtr);
    time = strtok_s(NULL, " ", &timePtr);
    dist = strtok_s(dist, " ", &distPtr);
    dist = strtok_s(NULL, " ", &distPtr);
    
    long long product = 1;
    while (time != NULL && dist != NULL) {
        int T = atoi(time);
        int d = atoi(dist);
        double sqr = sqrt(T*T-4*d);
        product *= ceil((T+sqr)/2)-floor((T-sqr)/2)-1;
        time = strtok_s(NULL, " ", &timePtr);
        dist = strtok_s(NULL, " ", &distPtr);
    }

    printf("%lld\n", product);
    return 0;
}