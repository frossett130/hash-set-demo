/**
 * Node structure of a doubly linked list.
 * @param value the string value, null if empty.
 * @param prev the previous node.
 * @param next the next node.
 */
struct node {
    char * value;
    struct node * prev;
    struct node * next;
};

typedef struct hashset {
    struct node ** array;
    unsigned long capacity;
    unsigned long size;
} hashset_t;

/**
 * Initialise the hash set.
 * @param initialcapacity the default allocated capacity,
 * will be set to zero if no available capacity encountered.
 * @return the initialised hash set.
 */
hashset_t init(unsigned long);

int push(hashset_t *, char *);

int pop(hashset_t *, char *);

int ispresent(hashset_t, char *);

int clear(hashset_t *);

int checksize(hashset_t *);
