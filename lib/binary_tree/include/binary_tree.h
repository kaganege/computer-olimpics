#pragma once

// #define __BT_NARG(...) __BT_NARG_PRIVATE(0, ##__VA_ARGS__, bt_create_with_left_right, bt_create_with_left, bt_create)
// #define __BT_NARG_PRIVATE(_0, _1_, _2_, f, ...) f
// #define BINARY_TREE(data, ...) __BT_NARG(##__VA_ARGS__)(data, ##__VA_ARGS__)

typedef struct binary_tree {
    struct binary_tree* left;
    struct binary_tree* right;
    int root;
} binary_tree_t;

binary_tree_t* bt_create(int root);
binary_tree_t* bt_create_with_left(int root, int left);
binary_tree_t* bt_create_with_left_right(int root, int left, int right);

void bt_dump(binary_tree_t* tree);
void bt_destroy(binary_tree_t* tree);
