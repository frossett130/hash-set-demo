#include "../lib/hashset.h"

void freerec(struct node *node)
{
    if (node)
    {
        freerec(node->next);
        free(node);
    }
}

void freehashset(hashset_t *hashset)
{
    for (int i = 0; i < hashset->capacity; i++)
    {
        freerec(hashset->array[i]);
    }
    free(hashset->array);
    free(hashset);
}
