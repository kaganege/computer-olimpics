#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "linked_list_node.h"

#define ll_for_each(pos, head) \
	for (pos = (head); pos != NULL; pos = pos->next)

#define ll_for_each_enumerate(i, pos, head) \
	for (i = 0, pos = (head); pos != NULL; ++i, pos = pos->next)

#define ll_for_each_custom(node_type, pos, head) \
    for (pos = (node_type *)(head); pos != NULL; pos = (node_type *)pos->next)

#define ll_for_each_custom_enumerate(i, node_type, pos, head) \
    for (i = 0, pos = (node_type *)(head); pos != NULL; ++i, pos = (node_type *)pos->next)

struct linked_list {
    size_t data_size;
    struct ll_node* head;
    struct ll_node* tail;
};

struct linked_list* ll_create(size_t data_size);
struct linked_list* ll_create_from_array(const void* data, size_t data_size, size_t count);
bool ll_is_empty(struct linked_list* list);
void ll_clear(struct linked_list* list);
void ll_destroy(struct linked_list* list);
void* ll_get(struct linked_list* list, size_t index);
void* ll_find(struct linked_list* list, const void* data);
size_t ll_index_of(struct linked_list* list, const void* data);
size_t ll_index_of_ptr(struct linked_list* list, const void* data);
void* ll_append(struct linked_list* list, const void* data);
void* ll_insert(struct linked_list* list, size_t index, const void* data);
void* ll_pop_front(struct linked_list* list);
void* ll_pop(struct linked_list* list);
void ll_remove(struct linked_list* list, size_t index);
bool ll_contains(struct linked_list* list, const void* data);
bool ll_contains_ptr(struct linked_list* list, const void* data);
size_t ll_size(struct linked_list* list);
void ll_to_array(struct linked_list* list, void* array, size_t count);
