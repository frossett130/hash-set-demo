#include<stdlib.h>
#define P 53

size_t expp(size_t n) {
    if (n) return P * expp(n - 1);
    return 1;
}

size_t hashcode(char * s, size_t m) {
    unsigned char * us = (unsigned char *) s;
    unsigned char p;
    size_t count = 0;
    size_t retval = 0;
    while ((p = us[count])) {
        retval += p * expp(count++);
    }
    return retval % m;
}
