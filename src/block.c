#include "../inc/malloc.h"

t_block    *add_new_block_to_heap(t_heap *heap, size_t size)
{
    t_block *last;
    t_block *new_block;
    void    *addr;
    size_t  required_size;

    required_size = size + sizeof(t_block);
    if (heap->free_size < required_size)
        return NULL;

    last = heap->first_block;
    while (last && last->next)
    {
        last = last->next;
    }
    if (!last)
        addr = HEAP_OFFSET(heap); //first b goes after heap metadata
    else
        addr = BLOCK_OFFSET(last) + last->size;
    if ((addr + required_size) > ((void *)heap + heap->total_size))//prevent writing past the heap
        return NULL;
    new_block = (t_block *)addr;
    setup_block(new_block, size);
    new_block->prev = last;
    if (last)
        last->next = new_block;
    else
        heap->first_block = new_block;
    heap->free_size -= sizeof(t_block) + new_block->size;
    heap->block_count++;

    return new_block;
}

t_block *get_available_block(t_heap *heap, size_t size)
{
    (void)size;
    return NULL;
}

void setup_block(t_block *block, size_t size)
{
    block->prev = NULL;
    block->next = NULL;
    block->free = 0;
    block->size = size;
}
