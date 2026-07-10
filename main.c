#include "./lib/hashset.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    hashset_t *set = init(4);
    for (int i = 1; i < argc; i++)
    {
        int result = push(&set, argv[i]);
        if (!result)
        {
            printf("You inserted `%s` at least twice.\n");
        }
    }
    for (int i = 0; i < set->capacity; i++)
    {
        printf("array[%02d]: ", i);
        struct node *noderef = set->array[i];
        while (noderef)
        {
            printf("`%s` -> ", noderef -> value);
            noderef = noderef -> next;
        }
        printf("\n");

    }
    freehashset(set);
    return 0;
}
