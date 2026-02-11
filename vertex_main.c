#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "vertex.h"

void dump_vertex(vertex_t* node, uint8_t level)
{
    if (node == NULL)
        return;

    printf("%*s%d\n", level * 2, "", node->data);

    if (node->children == NULL)
        return;

    assert(level < 0xFF);
    level++;

    for (size_t i = 0; i < node->child_count; i++)
    {
        dump_vertex(node->children[i], level);
    }
}

int main()
{
    vertex_t* node = vertex_create_with_fixed_children(56, 3);

    for (uint8_t i = 0; i < 3; i++)
        node->children[i] = vertex_create_with_children(i, 2, i + 1, i + 2);

    dump_vertex(node, 0);
    vertex_destroy(node);

    return 0;
}
