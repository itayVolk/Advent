/* Represents a hash table implemntation of a set
   Author: Itay Volk
   Date: 10/14/2024
*/

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "table.h"

typedef struct set{
    int count;
    int length;
    void **data;
    bool *flags;
    int (*compare)(void*, void*);
    unsigned (*hash)(void*);
} SET;

/* Searches the hash table
   Big O notation:
      Worst: O(n)
      Average: O(1)
      Best: O(1)
*/
static int search(SET *sp, void *elt, bool *found) {
    assert(sp != NULL && elt != NULL && found != NULL);
    if (sp->length == 0) {
        *found = false;
        return 0;
    }
    int empty = -1;
    unsigned hash = (*sp->hash)(elt);
    int i = 0;
    int loc = (hash + i)%sp->length;
    while(sp->flags[loc] && (sp->data[loc] == NULL || (*sp->compare)(elt, sp->data[loc]) != 0)) {
        if (sp->data[loc] == NULL) {
            empty = loc;
        }
        i++;
        assert(i < sp->length);
        loc = (hash + i)%sp->length;
    }
    *found = sp->flags[loc];
    return (*found || empty == -1) ? loc : empty;
}

/* Creates a new hash table
   Big O notation: O(1)
*/
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    assert(maxElts > 0);
    SET* sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->compare = compare;
    sp->hash = hash;
    sp->data = calloc(maxElts, sizeof(void*));
    assert(sp->data != NULL);
    sp->flags = calloc(maxElts, sizeof(bool));
    assert(sp->flags != NULL);
    return sp;
}

/* Destroys a hash table
   Big O notation: O(1)
*/
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
}

/* Returns the number of elements in a hash table
   Big O notation: O(1)
*/
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

/* Adds an element to the hash table
   Big O notation: O(1)
*/
void addElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int loc = search(sp, elt, &found);
    if (!found) {
        sp->flags[loc] = true;
        sp->data[loc] = elt;
        sp->count++;
    }
}

/* Removes an element from the hash table
   Big O notation: O(1)
*/
void removeElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int loc = search(sp, elt, &found);
    if (found) {
        sp->data[loc] = NULL;
        sp->count--;
    }
}

/* Returns a pointer to a copy of the element if found
   Big O notation: O(1)
*/
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    bool found;
    int loc = search(sp, elt, &found);
    if (found) {
        return sp->data[loc];
    }
    return NULL;
}

/* Returns an array containg the elements in the hash table
   Big O notation: O(m)
*/
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **out = calloc(sp->count, sizeof(void*));
    assert(out != NULL);
    int added = 0;
    for (int i = 0; i < sp->length; i++) {
        if (sp->data[i] != NULL) {
            out[added++] = sp->data[i];
        }
    }
    return out;
}