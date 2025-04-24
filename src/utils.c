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
