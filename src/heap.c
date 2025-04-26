#include "../inc/malloc.h"

int is_heap_empty(t_heap *heap)
{
    t_block *block;
    block = heap->first_block;
    while (block)
    {
        if (block->free == 1)
            return 0;
        block = block->next;
    }
    return 1;
}

t_heap *find_heap_from_block(t_block *block)
{
    t_heap *heap = g_first_heap;
    while (heap)
    {
        void *start = (void *)heap;
        void *end = start + heap->total_size;
        if ((void *)block > start && (void *)block < end)
            return heap;
        heap = heap->next;
    }
    return NULL;
}

size_t get_heap_size_from_block(size_t size)
{
    if (size <= TINY_BLOCK_SIZE)
        return (size_t)TINY_ZONE_SIZE;
    else if (size <= SMALL_BLOCK_SIZE)
        return (size_t)SMALL_ZONE_SIZE;
    else
        return (size + sizeof(t_block) + sizeof(t_heap));
}

t_heap *create_heap(size_t size)
{
    size_t  heap_size;
    t_heap  *heap;
    size_t mem_limit = get_system_limit();

    heap_size = get_heap_size_from_block(size);
    if (mem_limit && heap_size > mem_limit)
        return NULL;

    heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE ,
                 MAP_ANON | MAP_PRIVATE, -1, 0);
    if (heap == MAP_FAILED)
        return NULL;
    ft_bzero(heap, sizeof(heap));
    heap->zone = determine_zone(size);
    heap->total_size = heap_size;
    heap->free_size = heap_size - sizeof(t_heap);
    heap->block_count = 0;
    return heap;
}

t_heap  *find_heap(t_heap_type zone, size_t size, t_heap *first_heap)
{
    t_heap *tmp;

    tmp = first_heap;
    while (tmp)
    {
        if (tmp->zone == zone && tmp->free_size >= size)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

void add_heap_to_list(t_heap *new_heap)
{
    if (!g_first_heap)
    {
        g_first_heap = new_heap;
        return;
    }
    t_heap *tmp = g_first_heap;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_heap;
    new_heap->prev = tmp;
}

t_heap  *get_available_heap(size_t block_size)
{
    t_heap      *heap;
    t_heap      *first_heap;

    first_heap = g_first_heap;

    heap = find_heap(determine_zone(block_size), block_size, first_heap);
    if (!heap)
    {
        if (!(heap = create_heap(block_size)))
            return NULL;
        add_heap_to_list(heap);
    }
    return heap;
}
