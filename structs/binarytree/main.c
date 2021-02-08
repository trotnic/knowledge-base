#include "headers/binarytree.h"

void printing(void *value, int key) {
    printf("%d\t", key);
}

/*
*           _
*           6
*          / \
*        1    12
*             / \
*            9   15
*           / \
*          7   10
*          -

*  after deleting 6
*  element 7 replaces it 
*  as the successor

*          7
*         / \
*        1   12
*           /  \
*          9    15
*           \
*            10
*/



/*
 *          12
 *         /  \
 *       10    20
 *      /  \    \
 *     2    11   23
 *    / \         \
 *   1   5         24
 */

int main(int argc, char const *argv[])
{
    int *data, i = 123;
    data = &i;
    t_node *node = new(data, 12);
    insert(&node, data, 10);
    insert(&node, data, 11);
    insert(&node, data, 2);
    insert(&node, data, 1);
    insert(&node, data, 5);
    insert(&node, data, 20);
    insert(&node, data, 23);
    insert(&node, data, 24);

    puts("preorder");
    preorder(node, printing);
    puts("\n");
    puts("inorder");
    inorder(node, printing);
    puts("\n");
    puts("postorder");
    postorder(node, printing);
    puts("");
//    printf("%d\n", *((int*)get_value(successor(search_chaining(node, 2)))));
    return 0;
}