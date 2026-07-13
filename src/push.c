#include "../lib/hashset.h"

int hashtableiterate(size_t i, hashset_t hashset, hashset_t **newset)
{
    struct node *noderef = hashset.array[i];
    while (noderef)
    {
        int retval = push(newset, noderef->value);
        if (retval < 0)
        {
            return retval;
        }
        noderef = noderef->next;
    }
    return 1;
}

int increasecapacity(hashset_t **hashset, size_t newcapacity)
{
    int retval;
    hashset_t *newset = init(newcapacity);
    if (!newset)
    {
        return -1;
    }
    for (size_t i = 0; i < (*hashset)->capacity; i++)
    {
        if ((retval = hashtableiterate(i, **hashset, &newset)) < 0)
        {
            break;
        }
    }
    if (retval < 0)
    {
        freehashset(newset);
    }
    else
    {
        freehashset(*hashset);
        *hashset = newset;
    }
    return retval;
}

int resize(hashset_t **hashset)
{
    int newsize = (*hashset)->size + 1;
    int capacity = (*hashset)->capacity;
    int newcapacity = capacity;
    while ((float)newsize / (float)newcapacity > LOAD_FACTOR && newcapacity < MAX_CAPACITY)
    {
        newcapacity *= 2;
    }
    if (capacity != newcapacity)
    {
        return increasecapacity(hashset, newcapacity);
    }
    (*hashset)->size = newsize;
    return 1;
}

int push(hashset_t **hashset, char *value)
{
    size_t hash;
    if (nodecontains(**hashset, value, &hash))
    {
        return 0;
    }
    struct node *newnode = malloc(sizeof(struct node));
    if (!newnode)
    {
        return -1;
    }
    struct node **oldnode = (*hashset)->array + hash;
    newnode->next = *oldnode;
    newnode->prev = NULL;
    newnode->value = value;
    if (*oldnode)
    {
        (*oldnode)->prev = newnode;
    }
    *oldnode = newnode;
    return resize(hashset);
}
