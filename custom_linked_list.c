#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "linked_list.h"

LL_NODE_CUSTOM(int, custom_ll_node);

int main()
{
    int data[] = { 1, 2, 3, 4, 5 };
    struct linked_list* list = ll_create_from_array(data, sizeof(int), 5);

    struct custom_ll_node* node;
    ll_for_each_custom(struct custom_ll_node, node, list->head)
        printf("%d\n", node->data);

    return 0;
}
