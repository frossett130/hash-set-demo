#include "../lib/hashset.h"
#include <stdlib.h>
#include <string.h>

size_t hashcode(char *, size_t);

int containsrec(char * value, struct node ** noderef) {
    if (!((*noderef) -> value)) {
        return 0;
    }
    if (!strcmp(value, (*noderef) -> value)) {
        return 1;
    }
    if (!(*noderef) -> next) {
        return 0;
    }
    * noderef = (* noderef) -> next;
    return containsrec(value, noderef);
}


int nodecontains(hashset_t hashset, char * value, struct node ** noderef) {
    * noderef = hashset.array + hashcode(value, hashset.capacity);
    return containsrec(value, noderef);
}