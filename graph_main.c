#include <stdio.h>

#include "graph.h"

void euler_formula(struct graph* graph)
{
    size_t vertex_count = graph->vertex_count;
    size_t edge_count = graph_edge_count(graph);
    size_t face_count = graph_face_count(graph);

    printf("vertex_count: %zu\n", vertex_count);
    printf("edge_count: %zu\n", edge_count);
    printf("face_count: %zu\n", face_count);

    assert(vertex_count - edge_count + face_count == 2);
}

int main()
{
    struct graph* graph = graph_create_with_capacity(4);

    vertex_t v1 = graph_add_vertex(graph, 1);
    vertex_t v2 = graph_add_vertex(graph, 2);
    vertex_t v3 = graph_add_vertex(graph, 3);
    vertex_t v4 = graph_add_vertex(graph, 4);

    graph_edge_add_undirected(graph, v1, v2);
    graph_edge_add_undirected(graph, v1, v3);
    graph_edge_add_undirected(graph, v2, v3);
    graph_edge_add_undirected(graph, v2, v4);
    graph_edge_add_undirected(graph, v3, v4);
    graph_edge_add_undirected(graph, v4, v1);

    graph_dump(graph);
    euler_formula(graph);

    graph_edge_remove_undirected(graph, v1, v4);

    graph_dump(graph);

    graph_destroy(graph);

    return 0;
}
