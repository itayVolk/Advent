/* 
   Author: Itay Volk
   Date: 12/27/2024
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char * getString(int pos, int len, char string[]) {
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

int getNum(char ** search, int width, int x, int y, int * second) {
    *second = -1;
    if (isdigit(search[y][x])) {
        int lbound = x;
        while (isdigit(search[y][lbound])) {
            lbound--;
        }
        lbound++;
        int rbound = x;
        while (isdigit(search[y][rbound])) {
            rbound++;
        }
        rbound--;
        return atoi(getString(lbound, rbound-lbound+1, search[y]));
    }
    int first = -1;
    if (x > 0 && isdigit(search[y][x-1])) {
        int bound = x-1;
        while (isdigit(search[y][bound])) {
            bound--;
        }
        bound++;
        first = atoi(getString(bound, x-bound, search[y]));
    }
    if (x < width-1 && isdigit(search[y][x+1])) {
        int bound = x+1;
        while (isdigit(search[y][bound])) {
            bound++;
        }
        bound--;
        if (first != -1) {
            *second = first;
        }
        return atoi(getString(x+1, bound-x, search[y]));
    }
    return first;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char **search = malloc(256*sizeof(char*));
    int height = 0;
    search[height] = calloc(256, sizeof(char));
    while(fgets(search[height], 256*sizeof(char), fp) != NULL) {
        search[++height] = calloc(256, sizeof(char));
    }
    
    int sum = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < strlen(search[y])-1; x++) {
            if (search[y][x] == '*') {
                int numA = -1;
                int numB = -1;
                if (x > 0 && isdigit(search[y][x-1])) {
                    int bound = x-1;
                    while(isdigit(search[y][bound])) {
                        bound--;
                    }
                    bound++;
                    numA = atoi(getString(bound, x-bound, search[y]));
                }
                if (x < strlen(search[y])-2 && isdigit(search[y][x+1])) {
                    int bound = x+1;
                    while(isdigit(search[y][bound])) {
                        bound++;
                    }
                    bound--;
                    if (numA == -1)
                        numA = atoi(getString(x+1, bound-x, search[y]));
                    else
                        numB = atoi(getString(x+1, bound-x, search[y]));
                }
                if (y > 0) {
                    int second;
                    int num = getNum(search, strlen(search[y])-1, x, y-1, &second);
                    if (num != -1) {
                        if (numA == -1) {
                            numA = num;
                        } else if (numB == -1) {
                            numB = num;
                        } else {
                            break;
                        }
                        if (second != -1) {
                            if (numB == -1) {
                                numB = second;
                            } else {
                                break;
                            }
                        }
                    }
                }
                if (y < height-1) {
                    int second;
                    int num = getNum(search, strlen(search[y])-1, x, y+1, &second);
                    if (num != -1) {
                        if (numA == -1) {
                            numA = num;
                        } else if (numB == -1) {
                            numB = num;
                        } else {
                            break;
                        }
                        if (second != -1) {
                            if (numB == -1) {
                                numB = second;
                            } else {
                                break;
                            }
                        }
                    }
                }
                if (numB != -1) {
                    sum += numA*numB;
                }
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}