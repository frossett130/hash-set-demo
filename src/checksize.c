#include "../lib/hashset.h"

int checksize(hashset_t *hashset)
{
    int size = 0;
    for (int i = 0; i < hashset->capacity; i++)
    {
        struct node * noderef = hashset->array[i];
        while (noderef)
        {
            size++;
            noderef = noderef -> next;
        }
    }
    if (size == hashset -> size)
    {
        return 0;
    }
    
    hashset -> size = size;
    
    return 1;
}