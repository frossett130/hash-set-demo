#include "../lib/hashset.h"

hashset_t *init(size_t initialcapacity)
{
    if (!initialcapacity)
    {
        return NULL;
    }
    hashset_t *retval = malloc(sizeof(hashset_t));
    if (!retval)
    {
        return NULL;
    }
    struct node **array;
    array = retval->array = calloc(initialcapacity, sizeof(void *));
    if (!array)
    {
        free(retval);
        return NULL;
    }
    retval->capacity = initialcapacity;
    retval->size = 0;
    return retval;
}