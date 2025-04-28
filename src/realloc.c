#include "../inc/malloc.h"

void    *initialize_realloc(void *ptr, size_t size)
{
    size_t  aligned_size;
    t_block *block;
    t_heap  *heap;

    aligned_size = ALIGN(size);
    block = (t_block *)((uint8_t *)ptr - sizeof(t_block));
    heap = find_heap_from_block(block);
    if (!heap)
    {
        pthread_mutex_unlock(&g_mutex_lock);
        return (NULL);
    }
    if (aligned_size <= block->size)
    {
        split_block(block, aligned_size, heap);
        pthread_mutex_unlock(&g_mutex_lock);
        return ptr;
    }
    if (block->next && block->next->free)
        if (grow_into_next_block(block, heap, aligned_size))
        {
            pthread_mutex_unlock(&g_mutex_lock);
            return ptr;
        }
    pthread_mutex_unlock(&g_mutex_lock);
    void *newp = malloc(aligned_size);
    if (!newp)
        return NULL;
    ft_memcpy(newp, ptr, block->size);
    free(ptr);
    return newp;
}

void    *realloc(void *ptr, size_t size)
{
    void    *new_ptr;
    if(!ptr)
        return malloc(size);
    if (!size)
    {
        free(ptr);
        return NULL;
    }
    pthread_mutex_lock(&g_mutex_lock);
    new_ptr = initialize_realloc(ptr, size);
    return new_ptr;
}
