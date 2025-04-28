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
    heap->free_size -= (sizeof(t_block) + new_block->size);
    heap->block_count++;

    return new_block;
}

void    defragment_blocks(t_heap *heap)
{
    while (heap)
    {
        t_block *block = HEAP_OFFSET(heap);
        while (block && block->next)
        {
            if (block->free && block->next->free)
            {
                t_block *next = block->next;
                block->size += sizeof(t_block) + next->size;
                block->next = next->next;
                if (next->next)
                    next->next->prev = block;
                heap->block_count--;
                heap->free_size += sizeof(t_block);
                continue;
            }
            block = block->next;
        }
        heap = heap->next;
    }
}

t_block *split_block(t_block *block,size_t size, t_heap *heap)
{
    size_t  total_size = size + sizeof(t_block);
    t_block *new;
    if (block->size >= total_size + sizeof(t_block) + 16)
    {
        new = (t_block *)BLOCK_OFFSET(block) + size;
        new->size = block->size - size - sizeof(t_block);
        new->free = 1;
        new->next = block->next;
        new->prev = block;
        if (block->next)
            block->next->prev = new;
        block->next = new;
        block->size = size;
        heap->block_count++;
        heap->free_size -= sizeof(t_block);
    }
    block->free = 0;
    heap->free_size -= block->size;
    return block;
}

t_block *get_available_block(size_t size)
{
    t_heap  *heap;
    t_block *block;

    t_heap_type zone = determine_zone(size);
    heap = g_first_heap;
    defragment_blocks(heap);
    while (heap)
    {
        block = HEAP_OFFSET(heap);
        while (heap->zone == zone && block)
        {
            if (block->free && block->size >= size)
                return split_block(block, size, heap);
            block = block->next;
        }
        heap = heap->next;
    }


    return NULL;
}

void setup_block(t_block *block, size_t size)
{
    block->prev = NULL;
    block->next = NULL;
    block->free = 0;
    block->size = size;
}

int    grow_into_next_block(t_block *block, t_heap *heap, size_t size)
{
    size_t combined;
    combined = block->size + sizeof(t_block) + block->next->size;
    if (combined >= size)
    {
        t_block *next = block->next;
        block->size = combined;
        block->next = next->next;
        if (next->next)
            next->next->prev = block;
        heap->block_count--;
        heap->free_size += sizeof(t_block);
        split_block(block, size, heap);
        return 1;
    }
    return 0;
}
