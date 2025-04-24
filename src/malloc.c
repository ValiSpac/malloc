#include "../inc/malloc.h"

void *initialize_malloc(size_t size)
{
    t_heap  *heap;
    t_block *block;
    size_t  zone_size;

    if (!size)
        return NULL;
    size_t total_block_size = ALIGN(size) + sizeof(t_block);
    heap = get_available_heap(total_block_size);
}

void *malloc(size_t size)
{
    void *add;
    pthread_mutex_lock(&g_mutex_lock);
    add = initialize_malloc(size);
    pthread_mutex_unlock(&g_mutex_lock);
}
