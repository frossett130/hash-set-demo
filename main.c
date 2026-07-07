#include "./lib/hashset.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    hashset_t hashset = init(16);
    push(&hashset, "hello");
    push(&hashset, "world");
    push(&hashset, "fun");
    for (int i = 0; i < argc; i++)
    {
        if (ispresent(hashset, argv[i]))
        {
            printf("`%s` is present\n", argv[i]);
        }
        else
        {
            printf("`%s` is not present\n", argv[i]);
        }
    }
    return 0;
}
