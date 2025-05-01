#include <errno.h>
#include <string.h>
#include "../libft/libft.h"
#include <assert.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define NUM_ALLOCATIONS 1000

__attribute__((visibility("default")))
void show_alloc_mem();

typedef struct s_allocs {
    char *tiny;
    char *small;
    char *large;
} t_allocs;

void *free_allocs(void *arg)
{
    t_allocs *allocs = (t_allocs *)arg;

    ft_putendl_fd("Freeing allocations in thread...", 1);

    if (allocs->tiny) free(allocs->tiny);
    if (allocs->small) free(allocs->small);
    if (allocs->large) free(allocs->large);

    ft_putendl_fd("Memory freed in thread. Showing memory:", 1);
    show_alloc_mem();

    return NULL;
}

int is_aligned_16(void *ptr)
{
    return ((uintptr_t)ptr & 0xF) == 0;
}

int main() {
    pthread_t tid;
    t_allocs allocs;

    allocs.tiny = malloc(64);
    assert(allocs.tiny);
    memcpy(allocs.tiny, "tiny test", 10);

    allocs.small = malloc(512);
    assert(allocs.small);
    memcpy(allocs.small, "small test", 11);

    allocs.large = malloc(20000);
    assert(allocs.large);
    memcpy(allocs.large, "large test", 11);

    ft_putendl_fd("\nMain thread: Memory allocated.", 1);
    show_alloc_mem();

    if (pthread_create(&tid, NULL, free_allocs, &allocs) != 0)
    {
        ft_putendl_fd("Failed to create thread", 2);
        exit(1);
    }

    pthread_join(tid, NULL);

    ft_putendl_fd("Back in main thread. Showing memory:", 1);
    show_alloc_mem();

    ft_putendl_fd(" \n---0-byte allocation test", 1);
    void *zero = malloc(0);
    if (!zero)
        ft_putendl_fd("Allocation is NULL\n", 1);

    ft_putendl_fd(" ---Alignment test ", 1);
    void *aligned = malloc(31);
    if (((size_t)aligned & 0xF) != 0)
    {
        ft_putendl_fd("Not aligned!!!", 2);
        exit(1);
    }
    ft_putendl_fd("Memory is aligned.\n", 1);
    free(aligned);

    ft_putendl_fd(" ---Multiple allocations", 1);
    char *arr[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ALLOCATIONS; i++)
    {
        arr[i] = malloc(128);
        assert(arr[i]);
        arr[i][0] = 'a';
        free(arr[i]);
    }

    ft_putendl_fd("Finished allocating multiple blocks.\n", 1);

    ft_putendl_fd(" ---Heap growth test", 1);
    for (int i = 0; i < 100; i++) {
        void *ptr = malloc(4096);
        assert(ptr);
        free(ptr);
    }

    ft_putendl_fd("Heap growth test passed.\n", 1);

    ft_putendl_fd(" ---Block overwrite test", 1);
    char *buf = malloc(16);
    assert(buf);
    memset(buf, 'X', 15);
    buf[15] = '\0';
    free(buf);
    ft_putendl_fd("Overwrite done.\n", 1);

    ft_putendl_fd(" ---Integer alloc test", 1);
    int *nums = malloc(5 * sizeof(int));
    assert(nums);
    for (int i = 0; i < 5; i++)
        nums[i] = i * 10;
    for (int i = 0; i < 5; i++)
        assert(nums[i] == i * 10);
    free(nums);
    ft_putendl_fd("Stored integers successfully.\n", 1);

    ft_putendl_fd(" All tests passed \n", 1);

    return 0;
}

