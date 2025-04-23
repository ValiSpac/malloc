#include "../inc/malloc.h"

void *initialize_malloc(size_t size)
{
    t_heap  *heap;
    t_block *block;
    void    *res;

    if (size == NULL)
        return NULL;

    size_t aligned_size = ALIGN(size);
    if (!(heap = determine_zone(aligned_size)))
        create_heap(aligned_size);
}

void *malloc(size_t size)
{
    void *add;
    pthread_mutex_lock(&g_mutex_lock);
    add = initialize_malloc(size);
    pthread_mutex_unlock(&g_mutex_lock);
}
