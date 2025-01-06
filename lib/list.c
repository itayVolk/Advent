/* Represents a double linked circular list
   Author: Itay Volk
   Date: 10/29/2024
*/

#include <stdlib.h>
#include <assert.h>

typedef struct node{
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list{
    int count;
    NODE *head;
    int (*compare)(void*, void*);
} LIST;

/* Creates a new list
   Big O notation (always): O(1)
*/
LIST *createList(int (*compare)()) {
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->data = NULL;
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    lp->compare = compare;
    return lp;
}

/* Destroys a list and frees its memory
   Big O notation (always): O(n)
*/
void destroyList(LIST *lp) {
    assert(lp != NULL);
    lp->head = lp->head->next;
    while (lp->head->data != NULL) {
        NODE *temp = lp->head;
        lp->head = lp->head->next;
        free(temp);
    }
    free(lp->head);
    free(lp);
}

/* Returns how many items are in the list
   Big O notation (always): O(1)
*/
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

/* Adds a node to the start of the list
   Big O notation (always): O(1)
*/
void addFirst(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL);
    NODE *add = malloc(sizeof(NODE));
    assert(add != NULL);
    add->data = item;
    add->next = lp->head->next;
    add->prev = lp->head;
    add->next->prev = add;
    add->prev->next = add;
    lp->count++;
}

/* Adds a node to the end of the list
   Big O notation (always): O(1)
*/
void addLast(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL);
    NODE *add = malloc(sizeof(NODE));
    assert(add != NULL);
    add->data = item;
    add->next = lp->head;
    add->prev = lp->head->prev;
    add->next->prev = add;
    add->prev->next = add;
    lp->count++;
}

/* Removes the first node
   Big O notation (always): O(1)
*/
void *removeFirst(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    void *data = lp->head->next->data;
    lp->head->next = lp->head->next->next;
    lp->head->next->prev = lp->head;
    lp->count--;
    return data;
}

/* Removes the last node
   Big O notation (always): O(1)
*/
void *removeLast(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    void *data = lp->head->prev->data;
    lp->head->prev = lp->head->prev->prev;
    lp->head->prev->next = lp->head;
    lp->count--;
    return data;
}

/* Returns the data of the first node
   Big O notation (always): O(1)
*/
void *getFirst(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    return lp->head->next->data;
}

/* Returns the data of the last node
   Big O notation (always): O(1)
*/
void *getLast(LIST *lp) {
    assert(lp != NULL && lp->count > 0);
    return lp->head->prev->data;
}

/* Removes the data if the item is in the list
   Big O notation:
      Worst: O(n)
      Average: O(n)
      Best: O(1)
*/
void removeItem(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL && lp->compare != NULL);
    if (lp->count == 0) {
        return;
    }
    NODE *cur = lp->head->next;
    while(cur->data != NULL && lp->compare(cur->data, item) != 0) {
        cur = cur->next;
    }
    if (cur->data != NULL && lp->compare(cur->data, item) == 0) {
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        lp->count--;
    }
}

/* Returns the data if the item is found or NULL if not
   Big O notation:
      Worst: O(n)
      Average: O(n)
      Best: O(1)
*/
void *findItem(LIST *lp, void *item) {
    assert(lp != NULL && item != NULL && lp->compare != NULL);
    NODE *cur = lp->head->next;
    while(cur->data != NULL && lp->compare(cur->data, item) != 0) {
        cur = cur->next;
    }
    return (cur->data != NULL && lp->compare(cur->data, item) == 0) ? cur->data : NULL;
}

/* Returns an array of all the data
   Big O notation (always): O(n)
*/
void *getItems(LIST *lp) {
    assert(lp != NULL);
    void** out = calloc(lp->count, sizeof(void*));
    assert(out != NULL);
    NODE *cur = lp->head->next;
    for(int i = 0; i < lp->count; i++) {
        out[i] = cur->data;
        cur = cur->next;
    }
    return out;
}
