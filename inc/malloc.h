#pragma once

#include "../libft/libft.h"
#include <sys/resource.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

#define HEAP_OFFSET(start) ((void *)start + sizeof(t_heap))
#define BLOCK_OFFSET(start) ((void *)start + sizeof(t_block))

#define ALIGN(size) (((size) + 15) & ~15)

//pagesize on OS 4096B
//pagesize * 4 = 16 KB
//pagesize * 32 = 128 KB
#define TINY_ZONE_SIZE (getpagesize() * 4)
#define SMALL_ZONE_SIZE (getpagesize() * 32)
#define TINY_BLOCK_SIZE (TINY_ZONE_SIZE / 128) //128B per block
#define SMALL_BLOCK_SIZE (SMALL_ZONE_SIZE / 128) //1024B per block

extern pthread_mutex_t g_mutex_lock;

typedef struct s_malloc_data{
    t_heap  *tiny;
    t_heap  *small;
    t_heap  *large;
} t_malloc_data;
extern t_malloc_data g_malloc_data;

typedef struct s_heap {
    struct s_heap   *prev;
    struct s_heap   *next;
    size_t          total_size;
    size_t          free_size;
    size_t          block_count;
    t_block         *first_block;
} t_heap;

typedef struct s_block{
    struct s_block  *prev;
    struct s_block  *next;
    size_t          size;
    int             free;
} t_block;

void        setup_block(t_block *block, size_t size);
