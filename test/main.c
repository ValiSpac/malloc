#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../libft/libft.h"

int main(void)
{
    char *ptr = malloc(256);
    char *ptr1 = malloc(256);
    char *ptr2 = malloc(256);
    char *ptr3 = malloc(1698);
    if (!ptr || !ptr1 || !ptr2 || !ptr3)
    {
        dprintf(2,"%i\n", errno);
        return 1;
    }
    // strcpy(ptr, "Hello from ft_malloc!");
    // printf("Allocated: %s\n", ptr);
    // free(ptr);
    return 0;
}
