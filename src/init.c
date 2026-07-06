#include <stdlib.h>
#include "../lib/hashset.h"

hashset_t init(unsigned long initialcapacity) {
    hashset_t retval;
    struct node * array = retval.array = malloc(initialcapacity * sizeof(struct node));
    if (array) {
        for (int i = 0; i < initialcapacity; i++) {
            array[i].next = NULL;
            array[i].prev = NULL;
            array[i].value = NULL;
        }
    }
    retval.capacity = retval.array ? initialcapacity : 0;
    retval.size = 0;
    return retval;
}