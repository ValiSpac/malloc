#include "../inc/malloc.h"

t_heap *determine_zone(size_t size)
{
    if (size <= TINY_BLOCK_SIZE)
        return g_malloc_data.tiny;
    if (size > TINY_BLOCK_SIZE && size <= SMALL_BLOCK_SIZE)
        return g_malloc_data.small;
    else
        return g_malloc_data.large;
}

size_t get_heap_size_from_block
