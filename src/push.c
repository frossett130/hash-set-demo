#include "../lib/hashset.h"
#define MAX_RATIO 0.75
#define MAX_CAPACITY 1000000

void increasesize(hashset_t **hashset)
{
    int newsize = (*hashset)->size + 1;
    int capacity = (*hashset)->capacity;
    int newcapacity = capacity;
    while ((float)newsize / (float)newcapacity > MAX_RATIO && newcapacity < MAX_CAPACITY)
    {
        newcapacity *= 2;
    }
    if (capacity != newcapacity)
    {
        hashset_t *newset = init(newcapacity);
        for (int i = 0; i < capacity; i++)
        {
            struct node *noderef = (*hashset)->array[i];
            while (noderef)
            {
                push(&newset, noderef->value);
                noderef = noderef->next;
            }
        }
        freehashset(*hashset);
        *hashset = newset;
    }
    else
    {
        (*hashset)->size = newsize;
    }
}

int push(hashset_t **hashset, char *value)
{
    struct node *noderef;
    if (nodecontains(**hashset, value, &noderef))
    {
        return 0;
    }
    struct node *newnode = malloc(sizeof(struct node));
    if (!newnode)
    {
        return -1;
    }
    if (noderef)
    {
        noderef->next = newnode;
    }
    else
    {
        (*hashset)->array[hashcode(value, (*hashset)->capacity)] = newnode;
    }
    newnode->prev = noderef;
    newnode->value = value;
    newnode->next = NULL;
    increasesize(hashset);
    return 1;
}