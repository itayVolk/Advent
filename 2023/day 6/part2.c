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
    long long T = 0;
    long long d = 0;

    while(time != NULL && dist != NULL) {
        T *= pow(10, strlen(time));
        if (time[strlen(time)-1] == '\n') {
            T /= 10;
        }
        T += atoll(time);
        time = strtok_s(NULL, " ", &timePtr);
        d *= pow(10, strlen(dist));
        if (dist[strlen(dist)-1] == '\n') {
            d /= 10;
        }
        d += atoll(dist);
        dist = strtok_s(NULL, " ", &distPtr);
    }
    
    double sqr = sqrt(T*T-4*d);
    printf("%lld\n", (long long)(ceil((T+sqr)/2)-floor((T-sqr)/2)-1));
    return 0;
}