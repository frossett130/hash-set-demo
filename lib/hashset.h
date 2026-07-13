#include <stdlib.h>

/**
 * Node structure of a doubly linked list.
 * @param value the string value, null if empty.
 * @param prev the previous node.
 * @param next the next node.
 */
struct node
{
    char *value;
    struct node *prev;
    struct node *next;
};

/**
 * Hash set structure.
 * @param array the array containing the pointers to the objects.
 * @param capacity the capacity of the set.
 * @param size the size of the set.
 */
typedef struct hashset
{
    struct node **array;
    size_t capacity;
    size_t size;
} hashset_t;

/**
 * Initialise the hash set.
 * @param initialcapacity the default allocated capacity,
 * will be set to zero if no available capacity encountered.
 * @return the pointer to the initialised hash set, null if memory
 * issues occurred.
 */
hashset_t *init(size_t);

/**
 * Push an element into the set.
 * @param hashset the pointer's reference to the hash set.
 * @param value the value to be pushed.
 * @return 0 if the element was already present,
 * 1 if the element has been successfully pushed,
 * -1 if there was no sufficient memory to perform the operation.
 */
int push(hashset_t **restrict, char *restrict);

/**
 * Pop an element from the set.
 * @param hashset the pointer to the hash set.
 * @param value the value to be popped.
 * @return the popped value if present, null otherwise
 */
char *pop(hashset_t *restrict, char *restrict);

/**
 * Check if an element is present in the set.
 * @param hashset the hash set.
 * @param value the value to be checked
 * @return the matched string, null otherwise.
 */
char *ispresent(hashset_t, char *);

/**
 * Clears the hash set, it cannot be used after this.
 * @param hashset the pointer to the hash set.
 */
void freehashset(hashset_t *);

/**
 * Check and fix the size in the cache.
 * @param hashset the pointer to the hashset;
 * @return 1 if the size was altered, 0 if nothing was done.
 */
int checksize(hashset_t *);

#ifdef LINK_BUILD
#define MAX_STR_LEN 1024
#define MAX_RATIO 0.75
#define MAX_CAPACITY 1048576
struct node *nodecontains(hashset_t, char *restrict, size_t *restrict);
#endif
