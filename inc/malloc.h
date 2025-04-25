#pragma once

#include "../libft/libft.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>

#define HEAP_OFFSET(start) ((void *)start + sizeof(t_heap))
#define BLOCK_OFFSET(start) ((void *)start + sizeof(t_block))

#define ALIGN(size) (((size) + 15) & ~15)

//pagesize on OS 4096B
//pagesize * 4 = 16 kB
//pagesize * 32 = 128 kB
#define TINY_ZONE_SIZE (size_t)(getpagesize() * 4)
#define SMALL_ZONE_SIZE (size_t)(getpagesize() * 32)
#define TINY_BLOCK_SIZE (size_t)(TINY_ZONE_SIZE / 128) //128B per block
#define SMALL_BLOCK_SIZE (size_t)(SMALL_ZONE_SIZE / 128) //1024B per block

typedef enum e_heap_type {
    HEAP_TINY,
    HEAP_SMALL,
    HEAP_LARGE
} t_heap_type;

typedef struct s_block{
    struct s_block  *prev;
    struct s_block  *next;
    size_t          size;
    int             free;
} t_block;

typedef struct s_heap {
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t          total_size;
    size_t          free_size;
    size_t          block_count;
    t_heap_type     zone;
    t_block         *first_block;
    uint8_t         _pad[8];//padding so the struct is aligned to 16 bytes
}__attribute__((aligned(16))) t_heap;

extern pthread_mutex_t  g_mutex_lock;
extern t_heap           *g_first_heap;

void        setup_block(t_block *block, size_t size);
t_heap      *get_available_heap(size_t block_size);
t_block     *get_available_block(size_t size);
t_heap_type determine_zone(size_t size);
t_block     *add_new_block_to_heap(t_heap *heap, size_t size);
void        print_size(size_t n);
size_t      get_system_limit();
