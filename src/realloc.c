#include "../inc/malloc.h"

//dummt realloc for testing
void *realloc(void *ptr, size_t size)
{
    void *new_ptr;

    if (!ptr)
        return malloc(size);
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    free(ptr);
    return new_ptr;
}
