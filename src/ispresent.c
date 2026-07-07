#include "../lib/hashset.h"
#include <stdlib.h>
#include <string.h>
#define P 53

size_t expp(size_t n) {
    if (n) return P * expp(n - 1);
    return 1;
}

size_t hashcode(char * s, size_t m) {
    unsigned char * us = (unsigned char *) s;
    unsigned char p;
    size_t count = 0;
    size_t retval = 0;
    while ((p = us[count])) {
        retval += p * expp(count++);
    }
    return retval % m;
}

int containsrec(char * value, struct node ** noderef) {
    if (!(* noderef)) {
        return 0;
    }
    if (!strcmp(value, (* noderef) -> value)) {
        return 1;
    }
    if (!(*noderef) -> next) {
        return 0;
    }
    * noderef = (* noderef) -> next;
    return containsrec(value, noderef);
}

int nodecontains(hashset_t hashset, char * value, struct node ** noderef) {
    * noderef = hashset.array[hashcode(value, hashset.capacity)];
    return containsrec(value, noderef);
}

int ispresent(hashset_t hashset, char * value) {
    struct node * _;
    return nodecontains(hashset, value, &_);
}