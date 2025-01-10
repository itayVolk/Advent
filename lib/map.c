/* Represents a hash map implementation of a set
   Author: Itay Volk
   Date: 10/29/2024
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "list.h"

typedef struct set {
    int count;
    int length;
    LIST ** lists;
    int (*compare)(void*, void*);
    unsigned (*hash)(void*);
} SET;

/* Creates a set
   Big O notation (always): O(m)
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    assert(maxElts > 0);
    SET * sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts/20;
    sp->compare = compare;
    sp->hash = hash;
    sp->lists = calloc(sp->length, sizeof(LIST *));
    assert(sp->lists != NULL);
    for (int i = 0; i < sp->length; i++) {
        sp->lists[i] = createList(sp->compare);
    }
    return sp;
}

/* Destorys the set
   Big O notation (always): O(m)
*/
void destroySet(SET *sp) {
    assert(sp != NULL);
    for (int i = 0; i < sp->length; i++) {
        destroyList(sp->lists[i]);
    }
    free(sp->lists);
    free(sp);
}

/* Returns the number of elements in the set
   Big O notation (always): O(1)
*/
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/* Returns the data if the item is found or NULL if not
   Big O notation:
      Worst: O(n)
      Average: O(1)
      Best: O(1)
*/
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    return findItem(sp->lists[sp->hash(elt)%sp->length], elt);
}

/* Adds the data to the set if it's not in it already
   Big O notation:
      Worst: O(n)
      Average: O(1)
      Best: O(1)
*/
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL && sp->count < sp->length*20);
    assert(!findElement(sp, elt));
    addFirst(sp->lists[sp->hash(elt)%sp->length], elt);
    sp->count++;
}

/* Removes the data if the item is in the set
   Big O notation:
      Worst: O(n)
      Average: O(1)
      Best: O(1)
*/
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL && sp->count > 0);
    removeItem(sp->lists[sp->hash(elt)%sp->length], elt);
    sp->count--;
}

/* Returns an array of all the data in the set
   Big O notation (always): O(n)
*/
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **out = calloc(sp->count, sizeof(void*));
    assert(out != NULL);
    int loc = 0;
    for (int i = 0; i < sp->length; i++) {
        int size = numItems(sp->lists[i]);
        memcpy(out+loc, getItems(sp->lists[i]), sizeof(void*)*size);
        loc += size;
    }
    return out;
}