#pragma once

#include <stdlib.h>
#include <string.h>

#define LL_NODE_SIZE(data_size) (sizeof(struct ll_node) + data_size)
#define LL_NODE_DATA_PTR(node_ptr) ((void*)((char*)(node_ptr) + sizeof(struct ll_node)))

#define LL_NODE_CUSTOM(type, name) \
    struct name { \
        struct ll_node; \
        type data; \
    }

struct ll_node {
    struct ll_node* next;
};

inline struct ll_node* ll_create_node_empty(size_t data_size)
{
    return (struct ll_node*)calloc(1, LL_NODE_SIZE(data_size));
}

inline struct ll_node* ll_create_node(const void* data, size_t data_size)
{
    struct ll_node* node = (struct ll_node*)malloc(LL_NODE_SIZE(data_size));

    if (node == NULL)
        return NULL;

    node->next = NULL;
    memcpy(LL_NODE_DATA_PTR(node), data, data_size);

    return node;
}
