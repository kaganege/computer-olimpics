#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "binary_tree.h"

typedef enum {
    BT_NODE_LEFT = 'L',
    BT_NODE_RIGHT = 'R',
} bt_node_t;

binary_tree_t* bt_create(int root)
{
    binary_tree_t* tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));
    tree->root = root;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

binary_tree_t* bt_create_with_left(int root, int left)
{
    binary_tree_t* tree = bt_create(root);
    tree->left = bt_create(left);

    return tree;
}

binary_tree_t* bt_create_with_left_right(int root, int left, int right)
{
    binary_tree_t* tree = bt_create(root);
    tree->left = bt_create(left);
    tree->right = bt_create(right);

    return tree;
}

static void bt_dump_inner(binary_tree_t* tree, uint8_t level, bt_node_t type)
{
    if (tree == NULL)
        return;

    printf("%*s%c: %d\n", level * 2, "", type, tree->root);

    bt_dump_inner(tree->left, level + 1, BT_NODE_LEFT);
    bt_dump_inner(tree->right, level + 1, BT_NODE_RIGHT);
}

void bt_dump(binary_tree_t* tree)
{
    printf("Root: ");

    if (tree == NULL)
    {
        printf("NULL\n");
        return;
    }

    printf("%d\n", tree->root);

    bt_dump_inner(tree->left, 1, BT_NODE_LEFT);
    bt_dump_inner(tree->right, 1, BT_NODE_RIGHT);
}

void bt_destroy(binary_tree_t* tree)
{
    if (tree == NULL) return;
    if (tree->left != NULL) bt_destroy(tree->left);
    if (tree->right != NULL) bt_destroy(tree->right);

    free(tree);
}
