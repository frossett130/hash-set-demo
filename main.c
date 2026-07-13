#include "./lib/hashset.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc == 1) {
        puts("USAGE");
        printf("%s arguments...\n", argv[0]);
        puts("Showcases the hashset functionalities. A hashset is built with");
        puts("the arguments in input, and the ensuing hashset structure is");
        puts("displayed.");
        return 1;
    }
    hashset_t *set = init(4);
    for (int i = 1; i < argc; i++)
    {
        int result = push(&set, argv[i]);
        switch(result)
        {
            case -1:
                printf("Memory allocation error!\n");
                return 2;
            case 0:
                printf("You insert `%s` at least twice\n", argv[i]);
        }
    }
    for (int i = 0; i < set->capacity; i++)
    {
        printf("array[%02d]", i);
        struct node *noderef = set->array[i];
        while (noderef)
        {
            printf(" -> `%s`", noderef -> value);
            noderef = noderef -> next;
        }
        printf("\n");

    }
    freehashset(set);
    return 0;
}
