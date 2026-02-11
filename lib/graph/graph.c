#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "recalloc.h"
#include "graph.h"
#include "linked_list.h"
#include "ensure_not_null.h"

struct graph* graph_create()
{
    struct graph* graph = (struct graph*)malloc(sizeof(struct graph));
    graph->vertex_count = 0;
    graph->vertices = ll_create(sizeof(int));
    graph->edge_matrix_capacity = 0;
    graph->edge_matrix = NULL;

    return graph;
}

struct graph* graph_create_with_capacity(size_t vertex_count)
{
    struct graph* graph = graph_create();
    graph->edge_matrix_capacity = vertex_count * vertex_count;
    graph->edge_matrix = (bool*)calloc(graph->edge_matrix_capacity, sizeof(bool));

    return graph;
}

struct graph* graph_create_with_vertices(const int* vertices, size_t vertex_count)
{
    struct graph* graph = graph_create();
    graph->vertices = ll_create_from_array(vertices, sizeof(int), vertex_count);
    graph->edge_matrix_capacity = vertex_count * vertex_count;
    graph->edge_matrix = (bool*)calloc(graph->edge_matrix_capacity, sizeof(bool));

    return graph;
}

const vertex_t graph_add_vertex(struct graph* graph, int data)
{
    ENSURE_NOT_NULL(graph);

    ++graph->vertex_count;

    return ll_append(graph->vertices, &data);
}

void graph_edge_add_directed(struct graph* graph, const vertex_t v1, const vertex_t v2)
{
    ENSURE_NOT_NULL(graph);

    size_t required_capacity = graph->vertex_count * graph->vertex_count;

    if (graph->edge_matrix_capacity < required_capacity)
    {
        graph->edge_matrix = (bool*)recalloc(graph->edge_matrix, required_capacity * sizeof(bool), graph->vertex_count * graph->vertex_count * sizeof(bool));
        graph->edge_matrix_capacity = required_capacity;
    }

    size_t v1_index = ll_index_of_ptr(graph->vertices, v1);
    size_t v2_index = ll_index_of_ptr(graph->vertices, v2);

    graph->edge_matrix[v1_index + v2_index * graph->vertex_count] = true;
}

void graph_edge_remove_directed(struct graph* graph, const vertex_t v1, const vertex_t v2)
{
    ENSURE_NOT_NULL(graph);

    size_t required_capacity = graph->vertex_count * graph->vertex_count;

    if (graph->edge_matrix_capacity < required_capacity)
    {
        graph->edge_matrix = (bool*)recalloc(graph->edge_matrix, required_capacity * sizeof(bool), graph->vertex_count * graph->vertex_count * sizeof(bool));
        graph->edge_matrix_capacity = required_capacity;
    }

    size_t v1_index = ll_index_of_ptr(graph->vertices, v1);
    size_t v2_index = ll_index_of_ptr(graph->vertices, v2);

    graph->edge_matrix[v1_index + v2_index * graph->vertex_count] = false;
}

void graph_edge_add_undirected(struct graph* graph, const vertex_t v1, const vertex_t v2)
{
    ENSURE_NOT_NULL(graph);

    size_t required_capacity = graph->vertex_count * graph->vertex_count;

    if (graph->edge_matrix_capacity < required_capacity)
    {
        graph->edge_matrix = (bool*)recalloc(graph->edge_matrix, required_capacity * sizeof(bool), graph->vertex_count * graph->vertex_count * sizeof(bool));
        graph->edge_matrix_capacity = required_capacity;
    }

    size_t v1_index = ll_index_of_ptr(graph->vertices, v1);
    size_t v2_index = ll_index_of_ptr(graph->vertices, v2);

    graph->edge_matrix[v1_index + v2_index * graph->vertex_count] = true;
    graph->edge_matrix[v2_index + v1_index * graph->vertex_count] = true;
}

void graph_edge_remove_undirected(struct graph* graph, const vertex_t v1, const vertex_t v2)
{
    ENSURE_NOT_NULL(graph);

    size_t required_capacity = graph->vertex_count * graph->vertex_count;

    if (graph->edge_matrix_capacity < required_capacity)
    {
        graph->edge_matrix = (bool*)recalloc(graph->edge_matrix, required_capacity * sizeof(bool), graph->vertex_count * graph->vertex_count * sizeof(bool));
        graph->edge_matrix_capacity = required_capacity;
    }

    size_t v1_index = ll_index_of_ptr(graph->vertices, v1);
    size_t v2_index = ll_index_of_ptr(graph->vertices, v2);

    graph->edge_matrix[v1_index + v2_index * graph->vertex_count] = false;
    graph->edge_matrix[v2_index + v1_index * graph->vertex_count] = false;
}

size_t graph_edge_count(const struct graph* graph)
{
    ENSURE_NOT_NULL(graph);

    size_t count = 0;

    for (size_t i = 0; i < graph->vertex_count; i++)
        for (size_t j = i + 1; j < graph->vertex_count; j++)
            if (graph->edge_matrix[i + j * graph->vertex_count])
                ++count;

    return count;
}

size_t graph_face_count(const struct graph* graph)
{
    ENSURE_NOT_NULL(graph);

    // Euler's formula: V - E + F = 2
    return graph_edge_count(graph) - graph->vertex_count + 2;
}

void graph_dump(const struct graph* graph)
{
    ENSURE_NOT_NULL(graph);

    for (size_t i = 0; i < graph->vertex_count; i++)
    {
        printf("%d: ", *(int*)ll_get(graph->vertices, i));

        for (size_t j = 0; j < graph->vertex_count; j++)
            if (graph->edge_matrix[i + j * graph->vertex_count])
                printf("%d ", *(int*)ll_get(graph->vertices, j));

        printf("\n");
    }
}

void graph_destroy(struct graph* graph)
{
    if (graph == NULL)
        return;

    free(graph->vertices);
    free(graph->edge_matrix);
    free(graph);
}
