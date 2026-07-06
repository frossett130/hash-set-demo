#include <stdlib.h>
#include "../lib/hashset.h"

hashset_t init(unsigned long initialcapacity) {
    hashset_t retval;
    retval.array = calloc(initialcapacity, sizeof(struct node *));
    retval.capacity = retval.array ? initialcapacity : 0;
    retval.size = 0;
    return retval;
}