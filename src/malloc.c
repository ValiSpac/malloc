#include "../inc/malloc.h"
#include <stdio.h>

t_heap *g_first_heap = NULL;
pthread_mutex_t g_mutex_lock = PTHREAD_MUTEX_INITIALIZER;

void *initialize_malloc(size_t size)
{
    t_heap  *heap;
    t_block *block;

    if (!size)
        return NULL;
    size_t aligned_size = ALIGN(size);
    block = get_available_block(aligned_size);
    if (block)
        return BLOCK_OFFSET(block);
    heap = get_available_heap(aligned_size);
    if (!heap)
        return NULL;
    print_size(heap->total_size);
    block = add_new_block_to_heap(heap, size);
    print_size(heap->free_size);
    return BLOCK_OFFSET(block);
}

void *malloc(size_t size)
{
    void *add;
    pthread_mutex_lock(&g_mutex_lock);
    add = initialize_malloc(size);
    pthread_mutex_unlock(&g_mutex_lock);
    return add;
}
