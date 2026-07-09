#include "../lib/hashset.h"

void freerec(struct node *node)
{
    if (node)
    {
        freerec(node->next);
        free(node);
    }
}

void clear(hashset_t *hashset)
{
    for (int i = 0; i < hashset->capacity; i++)
    {
        freerec(hashset->array[i]);
    }
    free(hashset->array);
    hashset->array = NULL;
    hashset->capacity = 0;
    hashset->size = 0;
}
