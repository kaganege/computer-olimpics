#pragma once

#include <stdint.h>

#include "linked_list.h"

typedef int* vertex_t;

struct weighed_graph {
    size_t vertex_count;
    struct linked_list* vertices;

    size_t edge_array_capacity;
    struct linked_list** edges;
};

struct weighed_graph* weighed_graph_create();
struct weighed_graph* weighed_graph_create_fixed(size_t vertex_count);
struct weighed_graph* weighed_graph_create_with_vertices(int* vertices, size_t vertex_count);
vertex_t weighed_graph_add_vertex(struct weighed_graph* graph, int data);

void weighed_graph_add_edge_directed(struct weighed_graph* graph, vertex_t v1, vertex_t v2, uint32_t weight);
void weighed_graph_remove_edge_directed(struct weighed_graph* graph, vertex_t v1, vertex_t v2);

void weighed_graph_add_edge_undirected(struct weighed_graph* graph, vertex_t v1, vertex_t v2, uint32_t weight);
void weighed_graph_remove_edge_undirected(struct weighed_graph* graph, vertex_t v1, vertex_t v2);

void weighed_graph_dump(struct weighed_graph* graph);
void weighed_graph_destroy(struct weighed_graph* graph);
