#include "../lib/hashset.h"

char *pop(hashset_t *hashset, char *value)
{
    struct node *noderef;
    size_t hash;
    if (!(noderef = nodecontains(*hashset, value, &hash)))
    {
        return NULL;
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
    char *retval = noderef->value;
    free(noderef);
    hashset->size--;
    return value;
}
