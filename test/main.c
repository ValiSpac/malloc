#include <errno.h>
#include <string.h>
#include "../inc/malloc.h"
#include <assert.h>
#include <stdint.h>

#define NUM_ALLOCATIONS 1000

int is_aligned_16(void *ptr)
{
    return ((uintptr_t)ptr & 0xF) == 0;
}

int main(void) {
    ft_putstr(" Tiny allocation test \n");
    char *tiny = malloc(64);
    assert(tiny);
    memcpy(tiny, "tiny test", 10);
    ft_putstr("Tiny block at: ");
    show_alloc_mem();
    free(tiny);

    ft_putstr(" Small allocation test \n");
    char *small = malloc(512);
    assert(small);
    memcpy(small, "small test", 11);
    ft_putstr("Small block at: ");
    show_alloc_mem();
    free(small);

    ft_putstr(" Large allocation test \n");
    char *large = malloc(20000);
    assert(large);
    memcpy(large, "large test", 11);
    ft_putstr("Large block at: ");
    show_alloc_mem();
    free(large);


    ft_putstr(" 0-byte allocation test \n");
    void *zero = malloc(0);
    ft_putstr("0-byte malloc returned: ");
    show_alloc_mem();
    free(zero);

    ft_putstr(" Alignment test \n");
    void *aligned = malloc(31);
    if (((size_t)aligned & 0xF) == 0)
        ft_putstr("Aligned pointer at: ");
    show_alloc_mem();
    free(aligned);

    ft_putstr(" Multiple allocations \n");
    char *arr[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        arr[i] = malloc(128);
        assert(arr[i]);
        arr[i][0] = 'a';
        free(arr[i]);
    }
    show_alloc_mem();
    ft_putstr("Finished allocating multiple blocks.\n");

    ft_putstr(" Heap growth test \n");
    for (int i = 0; i < 100; i++) {
        void *ptr = malloc(4096);
        assert(ptr);
        free(ptr);
    }
    show_alloc_mem();
    ft_putstr("Heap growth test passed.\n");

    ft_putstr(" Block overwrite test \n");
    char *buf = malloc(16);
    assert(buf);
    memset(buf, 'X', 15);
    buf[15] = '\0';
    show_alloc_mem();
    free(buf);
    ft_putstr("Overwrite done.\n");

    ft_putstr(" Integer content test \n");
    int *nums = malloc(5 * sizeof(int));
    assert(nums);
    for (int i = 0; i < 5; i++) nums[i] = i * 10;
    for (int i = 0; i < 5; i++) assert(nums[i] == i * 10);
    show_alloc_mem();
    free(nums);
    ft_putstr("Stored integers successfully.\n");

    ft_putstr(" All tests passed \n");
    return 0;
}

