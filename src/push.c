#include "../lib/hashset.h"
#include <stdlib.h>
#define MAX_RATIO 0.75
#define MAX_CAPACITY 1000000

int nodecontains(hashset_t, char *, struct node **);

void increasesize(hashset_t * hashset) {
    int size = hashset -> size++;
    int capacity = hashset -> capacity;
    float ratio = (float) size / (float) capacity;
    if (ratio >= MAX_RATIO && capacity * 2 < MAX_CAPACITY) {
        hashset_t newset = init(capacity * 2);
        for(int i = 0; i < capacity; i++) {
            struct node node = hashset -> array[i];
            if (node.value) push(&newset, node.value);
            struct node * next = &node;
            while ((next = next -> next)) {
                push(&newset, next -> value);
            }
        }
        * hashset = newset;
    }
}

int push(hashset_t * hashset, char * value) {
    struct node * noderef;
    if (nodecontains(* hashset, value, &noderef)) {
        return 0;
    }
    if (!(noderef -> value)) {
        noderef -> value = value;
    }
    struct node * newnode;
    newnode = noderef -> next = malloc(sizeof(struct node));
    if (!newnode) {
        return -1;
    }
    newnode -> prev = noderef;
    newnode -> value = value;
    newnode -> next = NULL;
    increasesize(hashset);
    return 1;
}