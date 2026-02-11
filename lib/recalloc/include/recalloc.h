#pragma once

#include <stdlib.h>
#include <string.h>
#include <assert.h>

inline void* recalloc(void* ptr, size_t old_size, size_t new_size)
{
    if (new_size <= old_size)
        return ptr;

    void* new_ptr = realloc(ptr, new_size);

    if (new_ptr == NULL)
        return NULL;

    memset((char*)new_ptr + old_size, 0, new_size - old_size);

    return new_ptr;
}
