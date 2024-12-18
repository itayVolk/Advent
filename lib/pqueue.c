/* Represents a priority queue
   Author: Itay Volk
   Date: 11/11/2024
*/

#include <stdlib.h>
#include <assert.h>

#define parent(loc) (((loc)-1)/2)
#define left(loc) ((loc)*2+1)
#define right(loc) ((loc)*2+2)

typedef struct pqueue{
    int count;
    int length;
    void **data;
    int (*compare)(void *, void *);
} PQ;

/* Creates a new pq
   Big O notation (always): O(1)
*/
PQ *createQueue(int (*compare)()) {
    assert(compare != NULL);
    PQ* out = malloc(sizeof(PQ));
    assert(out != NULL);
    out->count = 0;
    out->length = 10;
    out->compare = compare;
    out->data = calloc(out->length, sizeof(void*));
    assert(out->data != NULL);
    return out;
}

/* Destroys the pq
   Big O notation (always): O(1)
*/
void destroyQueue(PQ *pq) {
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

/* Returns the number of entries in the pq 
   Big O notation (always): O(1)
*/
int numEntries(PQ *pq) {
    assert(pq != NULL);
    return pq->count;
}

/* Adds a new entry to the pq
   Big O notation:
      Worst: O(log n)
      Average: O(log n)
      Best: O(1)
*/
void addEntry(PQ *pq, void *entry) {
    assert(pq != NULL && entry != NULL);
    if (pq->count == pq->length) {
        pq->length += 10;
        pq->data = realloc(pq->data, pq->length*sizeof(void*));
    }
    int loc = pq->count;
    while(loc > 0 && pq->compare(pq->data[parent(loc)], entry) > 0) {
        pq->data[loc] = pq->data[parent(loc)];
        loc = parent(loc);
    }
    pq->data[loc] = entry;
    pq->count++;
}

/* Removes and returns the smallest entry from the pq
   Big O notation:
      Worst: O(log n)
      Average: O(log n)
      Best: O(1)
*/
void *removeEntry(PQ *pq) {
    assert(pq != NULL);
    assert(pq->count > 0);
    void* out = pq->data[0];
    pq->data[0] = pq->data[pq->count-1];
    int loc = 0;
    while(left(loc) < pq->count) {
        int picked = left(loc);
        if (right(loc) < pq->count && pq->compare(pq->data[right(loc)], pq->data[left(loc)]) < 0) {
            picked = right(loc);
        }
        if (pq->compare(pq->data[picked], pq->data[loc]) < 0) {
            void * temp = pq->data[loc];
            pq->data[loc] = pq->data[picked];
            pq->data[picked] = temp;
            loc = picked;
        } else {
            break;
        }
    }
    pq->count--;
    return out;
}