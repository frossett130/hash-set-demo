#include "../lib/hashset.h"

int pop(hashset_t *hashset, char *value)
{
    struct node *noderef;
    size_t hash;
    if (!(noderef = nodecontains(*hashset, value, &hash)))
    {
        return 0;
    }
    struct node *prev = noderef->prev;
    struct node *next = noderef->next;
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
