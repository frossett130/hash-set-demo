#include "../lib/hashset.h"

int pop(hashset_t *hashset, char *value)
{
    struct node *noderef;
    if (!nodecontains(*hashset, value, &noderef))
    {
        return 0;
    }
    struct node *prev = noderef->prev;
    struct node *next = noderef->next;
    size_t hash = hashcode(value, hashset->capacity);
    if (prev)
    {
        prev->next = next;
    }
    else
    {
        hashset->array[hash] = next;
    }
    if (next)
    {
        next->prev = prev;
    }
    free(noderef);
    hashset->size--;
    return 1;
}