#include <errno.h>
#include <string.h>
#include "../libft/libft.h"
#include <assert.h>
#include <stdint.h>

#define NUM_ALLOCATIONS 1000

void write_str(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    write(1, s, len);
}

void write_ptr(void *p) {
    uintptr_t val = (uintptr_t)p;
    char hex[20] = "0x";
    char digits[] = "0123456789abcdef";
    for (int i = (sizeof(uintptr_t) * 2) - 1; i >= 0; i--) {
        hex[2 + ((sizeof(uintptr_t) * 2 - 1) - i)] = digits[(val >> (i * 4)) & 0xF];
    }
    hex[2 + sizeof(uintptr_t) * 2] = '\n';
    write(1, hex, 2 + sizeof(uintptr_t) * 2 + 1);
}

int is_aligned_16(void *ptr) {
    return ((uintptr_t)ptr & 0xF) == 0;
}

int main(void) {
    write_str("==== Tiny allocation test ====\n");
    char *tiny = malloc(64);
    assert(tiny);
    memcpy(tiny, "tiny test", 10);
    write_str("Tiny block at: ");
    write_ptr(tiny);
    free(tiny);

    write_str("==== Small allocation test ====\n");
    char *small = malloc(512);
    assert(small);
    memcpy(small, "small test", 11);
    write_str("Small block at: ");
    write_ptr(small);
    free(small);

    write_str("==== Large allocation test ====\n");
    char *large = malloc(20000);
    assert(large);
    memcpy(large, "large test", 11);
    write_str("Large block at: ");
    write_ptr(large);
    free(large);


    write_str("==== 0-byte allocation test ====\n");
    void *zero = malloc(0);
    write_str("0-byte malloc returned: ");
    write_ptr(zero);
    free(zero);

    write_str("==== Alignment test ====\n");
    void *aligned = malloc(31);
    if (((size_t)aligned & 0xF) == 0)
        write_str("Aligned pointer at: ");
    write_ptr(aligned);
    free(aligned);

    write_str("==== Multiple allocations ====\n");
    char *arr[NUM_ALLOCATIONS];
    for (int i = 0; i < NUM_ALLOCATIONS; i++) {
        arr[i] = malloc(128);
        assert(arr[i]);
        arr[i][0] = 'a';
        free(arr[i]);
    }
    write_str("Finished allocating multiple blocks.\n");

    write_str("==== Heap growth test ====\n");
    for (int i = 0; i < 100; i++) {
        void *ptr = malloc(4096);
        assert(ptr);
        free(ptr);
    }
    write_str("Heap growth test passed.\n");

    write_str("==== Block overwrite test ====\n");
    char *buf = malloc(16);
    assert(buf);
    memset(buf, 'X', 15);
    buf[15] = '\0';
    free(buf);
    write_str("Overwrite done.\n");

    write_str("==== Integer content test ====\n");
    int *nums = malloc(5 * sizeof(int));
    assert(nums);
    for (int i = 0; i < 5; i++) nums[i] = i * 10;
    for (int i = 0; i < 5; i++) assert(nums[i] == i * 10);
    free(nums);
    write_str("Stored integers successfully.\n");

    write_str("==== All tests passed ====\n");
    return 0;
}

