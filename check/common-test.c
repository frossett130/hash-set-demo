#include "../lib/hashset.h"

hashset_t *testhashset()
{
    hashset_t *hashset = init(1);
    struct node *hello = malloc(sizeof(struct node));
    struct node *world = malloc(sizeof(struct node));
    struct node *fun = malloc(sizeof(struct node));
    hello->value = "hello";
    world->value = "world";
    fun->value = "fun";
    hello->next = world;
    world->next = fun;
    fun->next = NULL;
    hello->prev = NULL;
    world->prev = hello;
    fun->prev = world;
    hashset->array[0] = hello;
    hashset->size = 3;
}
