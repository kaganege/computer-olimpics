#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "recalloc.h"
#include "weighed_graph.h"
#include "linked_list.h"
#include "ensure_not_null.h"

struct weighed_edge {
    vertex_t connected_vertex;
    int weight;
};

static inline struct weighed_graph* __graph_create()
{
    struct weighed_graph* graph = (struct weighed_graph*)malloc(
        sizeof(struct weighed_graph)
    );

    if (graph == NULL)
        return NULL;

    graph->vertex_count = 0;
    graph->vertices = NULL;

    graph->edge_array_capacity = 0;
    graph->edges = NULL;

    return graph;
}

static inline void __graph_init_vertices(struct weighed_graph* graph)
{
    if (graph == NULL)
        return;

    graph->vertices = ll_create(sizeof(int));

    if (graph->vertices == NULL)
        weighed_graph_destroy(graph);
}

static inline void __graph_init_edges(struct weighed_graph* graph, size_t vertex_count)
{
    if (graph == NULL)
        return;

    graph->edge_array_capacity = vertex_count;
    graph->edges = (struct linked_list**)malloc(
        graph->edge_array_capacity * sizeof(struct linked_list*)
    );

    if (graph->edges == NULL)
        weighed_graph_destroy(graph);
}

struct weighed_graph* weighed_graph_create()
{
    struct weighed_graph* graph = __graph_create();
    __graph_init_vertices(graph);

    return graph;
}

struct weighed_graph* weighed_graph_create_fixed(size_t vertex_count)
{
    struct weighed_graph* graph = weighed_graph_create();
    __graph_init_edges(graph, vertex_count);

    return graph;
}

struct weighed_graph* weighed_graph_create_with_vertices(int* vertices, size_t vertex_count)
{
    struct weighed_graph* graph = __graph_create();

    graph->vertices = ll_create_from_array(vertices, sizeof(int), vertex_count);
    if (graph->vertices == NULL)
    {
        free(graph);
        return NULL;
    }

    __graph_init_edges(graph, vertex_count);

    return graph;
}

vertex_t weighed_graph_add_vertex(struct weighed_graph* graph, int data)
{
    ++ENSURE_NOT_NULL(graph)->vertex_count;

    return ll_append(graph->vertices, &data);
}

static inline void __graph_ensure_edges(struct weighed_graph* graph)
{
    if (graph->edge_array_capacity < graph->vertex_count)
    {
        graph->edges = (struct linked_list**)recalloc(
            graph->edges,
            graph->edge_array_capacity * sizeof(struct linked_list*),
            graph->vertex_count * sizeof(struct linked_list*)
        );
        graph->edge_array_capacity = graph->vertex_count;
    }
}

static inline struct linked_list* __vertex_get_edges(struct weighed_graph* graph, vertex_t vertex)
{
    size_t index = ll_index_of_ptr(graph->vertices, vertex);
    return graph->edges[index];
}

static inline void __vertex_init_edges(struct linked_list* edges)
{
    if (edges == NULL)
        edges = ENSURE_NOT_NULL(ll_create(sizeof(struct weighed_edge)));
}

void weighed_graph_add_edge_directed(struct weighed_graph* graph, vertex_t v1, vertex_t v2, uint32_t weight)
{
    __graph_ensure_edges(ENSURE_NOT_NULL(graph));

    struct linked_list* v1_edges = __vertex_get_edges(graph, v1);
    __vertex_init_edges(v1_edges);

    ll_append(v1_edges, &(struct weighed_edge) { v2, weight });
}

void weighed_graph_remove_edge_directed(struct weighed_graph* graph, vertex_t v1, vertex_t v2)
{
    __graph_ensure_edges(ENSURE_NOT_NULL(graph));

    struct linked_list* v1_edges = ENSURE_NOT_NULL(__vertex_get_edges(graph, v1));

    size_t v2_index = ll_index_of(v1_edges, v2);
    ll_remove(v1_edges, v2_index);
}

void weighed_graph_add_edge_undirected(struct weighed_graph* graph, vertex_t v1, vertex_t v2, uint32_t weight)
{
    __graph_ensure_edges(ENSURE_NOT_NULL(graph));

    struct linked_list* v1_edges = __vertex_get_edges(graph, v1);
    __vertex_init_edges(v1_edges);
    ll_append(v1_edges, &(struct weighed_edge) { v2, weight });

    struct linked_list* v2_edges = __vertex_get_edges(graph, v2);
    __vertex_init_edges(v2_edges);
    ll_append(v2_edges, &(struct weighed_edge) { v1, weight });
}

void weighed_graph_remove_edge_undirected(struct weighed_graph* graph, vertex_t v1, vertex_t v2)
{
    __graph_ensure_edges(ENSURE_NOT_NULL(graph));

    struct linked_list* v1_edges = ENSURE_NOT_NULL(__vertex_get_edges(graph, v1));
    struct linked_list* v2_edges = ENSURE_NOT_NULL(__vertex_get_edges(graph, v1));

    size_t v2_index = ll_index_of(v1_edges, v2);
    ll_remove(v1_edges, v2_index);

    size_t v1_index = ll_index_of(v2_edges, v1);
    ll_remove(v2_edges, v1_index);
}

void weighed_graph_dump(struct weighed_graph* graph)
{
    assert(graph != NULL);

    for (size_t i = 0; i < graph->vertex_count; i++)
    {
        printf("%d: ", *(vertex_t)ll_get(graph->vertices, i));

        for (size_t j = 0; j < graph->vertex_count; j++)
            if (graph->edges[i + j * graph->vertex_count])
                printf("%d ", *(vertex_t)ll_get(graph->vertices, j));

        printf("\n");
    }
}

void weighed_graph_destroy(struct weighed_graph* graph)
{
    if (graph == NULL)
        return;

    free(graph->vertices);
    free(graph->edges);
    free(graph);
}
