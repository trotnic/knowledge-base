#include "../headers/types.h"

/*
*       5
*      / \
*     2   10   for 10
*    / \    \   11 becomes successor
*   1   3    15   and 11 is the minimum in
*           /  \   the right subtree of 10
*         11    16
*/
t_node *successor_inorder(const t_node *tree, const t_node *node) {
    if (node->rightPtr) return minimum_chaining(node->rightPtr);
    /*      _
    *       5   for a 3 search begins from a root
    *      / \   so when a current key is greater than 3
    *     2   10   then this key becomes a possible successor
    *    / \    \   otherwise go to right subtree or stop algo whem keys are equal
    *   1   3    15
    *       -   /  \
    *         11    16
    */
    t_node *successor = NULL;
    while(tree) {
        if (node->key < tree->key) {
            successor = (t_node *)tree;
            tree = tree->leftPtr;
        }
        if (node->key > tree->key) tree = tree->rightPtr;
        if (node->key == tree->key) break;
    }
    return successor;
}

/*
*       5
*      / \
*     2   10   for 10
*    / \    \   11 becomes successor
*   1   3    15   and 11 is the minimum in
*           /  \   the right subtree of 10
*         11    16
*/
t_node *successor(const t_node *node) {
    if (node->rightPtr) return minimum_chaining(node->rightPtr);
    /*
    *       5
    *      / \
    *     2   10   for 3 successor is the first node
    *    / \    \   that has the right child which is not 3
    *   1   3    15
    *           /  \
    *         11    16
    */
    t_node *y = node->parentPtr;
    while (y && node == y->rightPtr) {
        node = y;
        y = y->parentPtr;
    }
    return y;
}