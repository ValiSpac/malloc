#include "../inc/malloc.h"

size_t get_system_limit()
{
    struct rlimit rlim;
    if (getrlimit(RLIMIT_DATA, &rlim) == 0)
    {
        if (rlim.rlim_cur == RLIM_INFINITY)
            return (size_t)-1;
        return rlim.rlim_cur;
    }
    return 0;
}

void    print_size(size_t n)
{
    char    buf[21];
    int     i = 20;

    buf[i--] = '\n';
    if (n == 0)
        buf[i--] = '0';
    else
    {
        while (n > 0)
        {
            buf[i--] = '0' + (n % 10);
            n /= 10;
        }
    }
    write(1, &buf[i + 1], 20 - i);
}

t_heap_type determine_zone(size_t size)
{
    if (size <= TINY_BLOCK_SIZE)
        return HEAP_TINY;
    else if (size <= SMALL_BLOCK_SIZE)
        return HEAP_SMALL;
    else
        return HEAP_LARGE;
}
