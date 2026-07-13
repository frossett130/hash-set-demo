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
    while (count < MAX_STR_LEN && (p = us[count++]))
    {
        retval += ((size_t)p) * multiplier;
        multiplier *= P;
    }
    return retval % m;
}

struct node *containsrec(char *value, struct node *noderef)
{
    if (noderef && strncmp(value, noderef->value, MAX_STR_LEN))
    {
        return containsrec(value, noderef->next);
    }
    return noderef;
}

struct node *nodecontains(hashset_t hashset, char *value, size_t *hash)
{
    *hash = hashcode(value, hashset.capacity);
    struct node *noderef = hashset.array[*hash];
    return containsrec(value, noderef);
}

char *ispresent(hashset_t hashset, char *value)
{
    size_t _;
    struct node *node = nodecontains(hashset, value, &_);
    return node ? node -> value : NULL;
}
