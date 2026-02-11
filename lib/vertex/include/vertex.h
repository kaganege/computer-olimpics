#pragma once

#include <stdint.h>

typedef struct vertex_t {
    int data;
    size_t child_count;
    struct vertex_t** children;
} vertex_t;

vertex_t* vertex_create(int data);
vertex_t* vertex_create_with_fixed_children(int data, size_t n);
vertex_t* vertex_create_with_children(int data, size_t n, ...);
void vertex_append(vertex_t* node, vertex_t* child);
void vertex_destroy(vertex_t* node);
