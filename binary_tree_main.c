#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "binary_tree.h"

int main()
{
    binary_tree_t* root = bt_create(56);
    root->left = bt_create_with_left_right(10, 5, 28);
    root->right = bt_create_with_left(34, 31);

    bt_dump(root);

    return 0;
}
