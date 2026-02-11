#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>

#include "vertex.h"

vertex_t* vertex_create(int data)
{
    vertex_t* node = (vertex_t*)malloc(sizeof(vertex_t));
    assert(node != NULL);

    node->data = data;
    node->children = NULL;

    return node;
}

vertex_t* vertex_create_with_fixed_children(int data, size_t n)
{
    if (n == 0)
        return vertex_create(data);

    vertex_t* node = (vertex_t*)malloc(sizeof(vertex_t));
    assert(node != NULL);

    node->data = data;
    node->child_count = n;
    node->children = (vertex_t**)calloc(n, sizeof(vertex_t*));
    assert(node->children != NULL);

    return node;
}

vertex_t* vertex_create_with_children(int data, size_t n, ...)
{
    if (n == 0)
        return vertex_create(data);

    vertex_t* node = vertex_create_with_fixed_children(data, n);

    va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++)
    {
        node->children[i] = vertex_create(va_arg(args, int));
    }

    va_end(args);

    return node;
}

void vertex_append(vertex_t* node, vertex_t* child)
{
    if (node == NULL)
        return;

    vertex_t** tmp = (vertex_t**)realloc(node->children, sizeof(vertex_t*) * (node->child_count + 1));
    assert(tmp != NULL);

    tmp[node->child_count++] = child;
    node->children = tmp;
}

void vertex_destroy(vertex_t* node)
{
    if (node == NULL)
        return;

    if (node->children != NULL)
    {
        for (size_t i = 0; i < node->child_count; i++)
            vertex_destroy(node->children[i]);

        free(node->children);
    }

    free(node);
}
