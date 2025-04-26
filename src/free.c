#include "../inc/malloc.h"

void    start_free(void *ptr)
{
    t_block *block;
    t_heap  *heap;

    block = (t_block *)((uint8_t *)ptr - sizeof(t_block));
    heap = find_heap_from_block(block);
    if (!heap)
        return;
    block->free = 1;
    heap->free_size += sizeof(t_block ) + block->size;
    defragment_blocks(heap);
    if (heap->free_size == heap->total_size - sizeof(t_heap))
    {
        if (heap->prev)
            heap->prev->next = heap->next;
        if (heap->next)
            heap->next->prev = heap->prev;
        if (heap == g_first_heap)
            g_first_heap = heap->next;
        munmap(heap, heap->total_size);
    }
}

void    free(void *ptr)
{
    if (!ptr)
        return;
    pthread_mutex_lock(&g_mutex_lock);
    start_free(ptr);
    pthread_mutex_unlock(&g_mutex_lock);
}
