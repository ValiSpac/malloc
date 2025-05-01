#include "../inc/malloc.h"

void put_hex(uintptr_t addr)
{
    const char *hex;
    char buffer[17];
    int i;

    hex = "0123456789ABCDEF";
    i = 16;
    while (i--)
    {
        buffer[i] = hex[addr % 16];
        addr /= 16;
    }
    write(1, "0x", 2);
    write(1, buffer, 16);
}

void put_zone_type(int zone)
{
    if (zone == 0)
        ft_putstr("TINY: ");
    else if (zone == 1)
        ft_putstr("SMALL: ");
    else
        ft_putstr("LARGE: ");
}

void show_alloc_mem()
{
    t_heap  *heap;
    size_t  total;
    t_block *block;
    uintptr_t start, end;

    pthread_mutex_lock(&g_mutex_lock);
    heap = g_first_heap;
    total = 0;
    while (heap)
    {
        put_zone_type(heap->zone);
        put_hex((uintptr_t) heap);
        write(1, "\n", 1);
        block = heap->first_block;
        while (block)
        {
            if (!block->free)
            {
                start = (uintptr_t)block + sizeof(t_block);
                end = start + block->size;
                put_hex(start);
                ft_putstr("-");
                put_hex(end);
                ft_putstr(": ");
                ft_putnbr_fd(block->size, 1);
                ft_putstr(" bytes\n");
                total += block->size;
            }
            block = block->next;
        }
        heap = heap->next;
    }
    ft_putstr("Total: ");
    ft_putnbr_fd(total, 1);
    ft_putstr(" bytes\n");
    pthread_mutex_unlock(&g_mutex_lock);
}
