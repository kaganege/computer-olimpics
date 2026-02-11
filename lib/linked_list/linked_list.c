#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "linked_list.h"
#include "linked_list_node.h"
#include "ensure_not_null.h"

static inline void* __clone_data(const struct ll_node* restrict node, size_t data_size)
{
    void* data = malloc(data_size);
    if (data == NULL)
        return NULL;

    memcpy(data, LL_NODE_DATA_PTR(node), data_size);

    return data;
}

struct linked_list* ll_create(size_t data_size)
{
    struct linked_list* list = malloc(sizeof(struct linked_list));
    list->head = NULL;
    list->tail = NULL;
    list->data_size = data_size;

    return list;
}

struct linked_list* ll_create_from_array(const void* data, size_t data_size, size_t count)
{
    struct linked_list* list = ll_create(data_size);

    if (count == 0)
        return list;

    assert(data != NULL);

    for (size_t i = 0; i < count; i++)
    {
        ll_append(list, (char*)data + i * data_size);
    }

    return list;
}

bool ll_is_empty(struct linked_list* list)
{
    return ENSURE_NOT_NULL(list)->head == NULL;
}

void ll_clear(struct linked_list* list)
{
    struct ll_node* node = ENSURE_NOT_NULL(list)->head;

    while (node != NULL)
    {
        struct ll_node* next = node->next;
        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

void ll_destroy(struct linked_list* list)
{
    if (list == NULL)
        return;

    ll_clear(list);
    free(list);

    list = NULL;
}

struct ll_node* get_node(struct linked_list* list, size_t index)
{
    size_t i;
    struct ll_node* node;

    ll_for_each_enumerate(i, node, list->head)
        if (i == index)
            break;

    return node;
}

void* ll_get(struct linked_list* list, size_t index)
{
    return LL_NODE_DATA_PTR(get_node(ENSURE_NOT_NULL(list), index));
}

void* ll_find(struct linked_list* list, const void* data)
{
    struct ll_node* node;

    ll_for_each(node, ENSURE_NOT_NULL(list)->head)
    {
        void* node_data = LL_NODE_DATA_PTR(node);
        if (memcmp(node_data, data, list->data_size) == 0)
            return node_data;
    }

    return NULL;
}

size_t ll_index_of(struct linked_list* list, const void* data)
{
    ENSURE_NOT_NULL(list);

    size_t index = 0;
    struct ll_node* node = list->head;

    while (true)
    {
        assert(node != NULL);

        if (memcmp(LL_NODE_DATA_PTR(node), data, list->data_size) == 0)
            return index;

        node = node->next;
        ++index;
    }
}

size_t ll_index_of_ptr(struct linked_list* list, const void* data)
{
    ENSURE_NOT_NULL(list);

    size_t index = 0;
    struct ll_node* node = list->head;

    while (true)
    {
        assert(node != NULL);

        if (LL_NODE_DATA_PTR(node) == data)
            return index;

        node = node->next;
        ++index;
    }
}

void* ll_append(struct linked_list* list, const void* data)
{
    struct ll_node* node = ll_create_node(data, ENSURE_NOT_NULL(list)->data_size);

    if (node == NULL)
        return NULL;

    if (list->head == NULL)
        list->head = node;
    else
        list->tail->next = node;

    list->tail = node;

    return LL_NODE_DATA_PTR(node);
}

void* ll_insert(struct linked_list* list, size_t index, const void* data)
{
    ENSURE_NOT_NULL(list);

    struct ll_node* current = ENSURE_NOT_NULL(
        index == 0
        ? list->head
        : get_node(list, index - 1)
    );
    struct ll_node* node = ll_create_node(data, list->data_size);
    node->next = current->next;
    current->next = node;

    return LL_NODE_DATA_PTR(node);
}

void* ll_pop_front(struct linked_list* list)
{
    ENSURE_NOT_NULL(list);
    struct ll_node* node = ENSURE_NOT_NULL(list->head);
    void* data = __clone_data(node, list->data_size);

    list->head = node->next;

    free(node);

    return data;
}

void* ll_pop(struct linked_list* list)
{
    ENSURE_NOT_NULL(list);
    struct ll_node* previous = ENSURE_NOT_NULL(list->head);
    struct ll_node* last;

    if (previous->next != NULL)
    {
        while (previous->next->next != NULL)
            previous = previous->next;
        last = previous->next;
    }
    else
        last = previous;

    void* data = __clone_data(last, list->data_size);

    previous->next = NULL;
    list->tail = previous;

    free(last);

    return data;
}

void ll_remove(struct linked_list* list, size_t index)
{
    ENSURE_NOT_NULL(list);

    struct ll_node* previous = ENSURE_NOT_NULL(
        index <= 1
        ? list->head
        : get_node(list, index - 1)
    );
    struct ll_node* current = previous->next;
    struct ll_node* new = current == NULL ? NULL : current->next;

    previous->next = new;

    free(current);
}

bool ll_contains(struct linked_list* list, const void* data)
{
    struct ll_node* node;

    ll_for_each(node, ENSURE_NOT_NULL(list)->head)
        if (memcmp(LL_NODE_DATA_PTR(node), data, list->data_size) == 0)
            return true;

    return false;
}

bool ll_contains_ptr(struct linked_list* list, const void* data)
{
    struct ll_node* node;

    ll_for_each(node, ENSURE_NOT_NULL(list)->head)
        if (LL_NODE_DATA_PTR(node) == data)
            return true;

    return false;
}

size_t ll_size(struct linked_list* list)
{
    if (ENSURE_NOT_NULL(list)->head == NULL)
        return 0;

    size_t size;
    struct ll_node* node;

    ll_for_each_enumerate(size, node, ENSURE_NOT_NULL(list)->head);

    return size + 1;
}

void ll_to_array(struct linked_list* list, void* array, size_t count)
{
    ENSURE_NOT_NULL(list);
    ENSURE_NOT_NULL(array);

    struct ll_node* node = ENSURE_NOT_NULL(list->head);

    for (size_t i = 0; i < count; i++, node = node->next)
    {
        void* array_ptr = (char*)array + i * list->data_size;
        memcpy(array_ptr, LL_NODE_DATA_PTR(node), list->data_size);
    }
}
