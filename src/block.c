#include "../inc/malloc.h"

void    *add_new_block_to_heap(t_heap *heap, size_t size)
{
    t_block *last;
    void    *addr;
}

t_block *get_available_block(size)
{
return NULL;
}

void setup_block(t_block *block, size_t size)
{
    block->prev = NULL;
    block->next = NULL;
    block->free = 0;
    block->size = size;
}
