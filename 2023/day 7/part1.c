/*
   Author: Itay Volk
   Date: 12/28/2024
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

typedef enum types {HIGH, PAIR, TWO_PAIR, THREE_KIND, FULL, FOUR_KIND, FIVE_KIND} TYPES;
typedef enum cards {TWO, THREE, FOUR, FIVE, SIX, SEVE, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} CARDS;
typedef struct hand {
    TYPES type;
    CARDS * hand;
    int bid;
} HAND;

static int compare(HAND * a, HAND * b) {
    if (a->type != b->type) {
        return a->type-b->type;
    }
    int i = 0;
    while (i < 5 && a->hand[i] == b->hand[i]) {
        i++;
    }
    if (i == 5) {
        return 0;
    }
    return a->hand[i]-b->hand[i];
}

CARDS char2card(char c) {
    if (isdigit(c)) {
        return c-'2';
    }
    if (c == 'T') {
        return TEN;
    }
    if (c == 'J') {
        return JACK;
    }
    if (c == 'Q') {
        return QUEEN;
    }
    if (c == 'K') {
        return KING;
    }
    return ACE;
}

int main() {
    FILE * fp = fopen("input.txt", "r");
    char line[256];

    PQ * hands = createQueue(compare);
    while(fgets(line, sizeof(line), fp) != NULL) {
        HAND * hand = malloc(sizeof(HAND));
        hand->hand = malloc(5*sizeof(CARDS));
        hand->type = HIGH;
        hand->bid = atoi(line+6);
        int * counts = calloc(13, sizeof(int));
        for (int i = 0; i < 5; i++) {
            hand->hand[i] = char2card(line[i]);
            counts[hand->hand[i]]++;
        }
        int two = 0;
        int three = 0;
        for (int i = 0; i < 13; i++) {
            if (counts[i] >= 4) {
                hand->type = FOUR_KIND+counts[i]-4;
                break;
            } else if (counts[i] == 3) {
                three++;
            } else if (counts[i] == 2) {
                two++;
            }
        }
        if (two == 1) {
            if (three == 1) {
                hand->type = FULL;
            } else {
                hand->type = PAIR;
            }
        } else if (two == 2) {
            hand->type = TWO_PAIR;
        } else if (three == 1) {
            hand->type = THREE_KIND;
        }
        addEntry(hands, hand);
    }

    long long sum = 0;
    int rank = 1;
    while (numEntries(hands) > 0) {
        sum += ((HAND *)removeEntry(hands))->bid*(rank++);
    }
    printf("%lld\n", sum);
    return 0;
}