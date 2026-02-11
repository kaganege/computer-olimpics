#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "linked_list.h"

void dump_node(const struct ll_node* node)
{
    printf("%c", *(char*)LL_NODE_DATA_PTR(node));
    printf(" -> %p\n", node->next);
}

void ll_dump(struct linked_list* list)
{
    putchar('[');
    if (list != NULL)
    {
        struct ll_node* node = list->head;

        if (node != NULL)
        {
            printf("%c", *(char*)LL_NODE_DATA_PTR(node));

            ll_for_each(node, node->next)
                printf(", %c", *(char*)LL_NODE_DATA_PTR(node));
        }
    }
    printf("]\n");
}

char main()
{
    struct linked_list* list = ll_create(sizeof(char));

    for (char i = '1'; i <= '4'; i++)
        ll_append(list, &i);

    struct ll_node* node;
    ll_for_each(node, list->head)
        dump_node(node);

    ll_dump(list); // [1, 2, 3, 4]

    char third = *(char*)ll_get(list, 2);
    printf("Third value: %c\n", third); // 3

    ll_remove(list, 1);
    ll_dump(list); // [1, 3, 4]

    char last_value = *(char*)ll_pop(list); // 4
    printf("Last value: %c\n", last_value);

    ll_dump(list); // [1, 3]

    char first_value = *(char*)ll_pop_front(list); // 1
    printf("First value: %c\n", first_value);

    ll_dump(list); // [3]

    char remained_value;
    ll_to_array(list, &remained_value, 1);
    printf("Remained value: %c\n", remained_value); // 3

    ll_clear(list);
    ll_dump(list); // []

    ll_destroy(list);

    return 0;
}
