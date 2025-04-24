#include "../inc/malloc.h"

void setup_block(t_block *block, size_t size)
{
    block->prev = NULL;
    block->next = NULL;
    block->free = 0;
    block->size = size;
}
