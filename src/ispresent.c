#include "../lib/hashset.h"
#include <string.h>
#define P 53

size_t hashcode(char *s, size_t m)
{
    unsigned char *us = (unsigned char *)s;
    unsigned char p;
    size_t count = 0;
    size_t retval = 0;
    size_t multiplier = 1;
    while ((p = us[count++]))
    {
        retval += ((size_t)p) * multiplier;
        multiplier *= P;
    }
    return retval % m;
}

int containsrec(char *value, struct node **noderef)
{
    if (!(*noderef))
    {
        return 0;
    }
    if (!strcmp(value, (*noderef)->value))
    {
        return 1;
    }
    if (!(*noderef)->next)
    {
        return 0;
    }
    *noderef = (*noderef)->next;
    return containsrec(value, noderef);
}

int nodecontains(hashset_t hashset, char *value, struct node **noderef)
{
    *noderef = hashset.array[hashcode(value, hashset.capacity)];
    return containsrec(value, noderef);
}

int ispresent(hashset_t hashset, char *value)
{
    struct node *_;
    return nodecontains(hashset, value, &_);
}