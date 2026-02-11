#pragma once

#include <stdint.h>

#include "linked_list.h"

typedef int* vertex_t;

struct graph {
    size_t vertex_count;
    struct linked_list* vertices;

    size_t edge_matrix_capacity;
    bool* edge_matrix;
};

struct graph* graph_create();
struct graph* graph_create_with_capacity(size_t vertex_count);
struct graph* graph_create_with_vertices(const int* vertices, size_t vertex_count);
const vertex_t graph_add_vertex(struct graph* graph, int data);

void graph_edge_add_directed(struct graph* graph, const vertex_t v1, const vertex_t v2);
void graph_edge_remove_directed(struct graph* graph, const vertex_t v1, const vertex_t v2);

void graph_edge_add_undirected(struct graph* graph, const vertex_t v1, const vertex_t v2);
void graph_edge_remove_undirected(struct graph* graph, const vertex_t v1, const vertex_t v2);

size_t graph_edge_count(const struct graph* graph);
size_t graph_face_count(const struct graph* graph);

void graph_dump(const struct graph* graph);
void graph_destroy(struct graph* graph);
