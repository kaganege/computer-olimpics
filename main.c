#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main()
{
    int* list = calloc(10, sizeof(int));
    int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    memcpy(list, src, sizeof(int) * 10);

    realloc(list, sizeof(int) * 20);

    memset(list + 10, 0, sizeof(int) * 10);

    return 0;
}
