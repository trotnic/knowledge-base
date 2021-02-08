#include "../headers/types.h"

/*
 *       5
 *      / \
 *     2   10   for 5
 *    / \    \   3 becomes predecessor
 *   1   3    15   and 3 is the maximum in
 *           /  \   the left subtree of 5
 *         11    16
 */
t_node *predecessor_inorder(const t_node *tree, const t_node *node) {
    if (node->leftPtr) return maximum_chaining(node->leftPtr);
    /*      
    *       5   for a 10 search begins from a root
    *      / \   so when a current key is less than 10
    *     2   10   then this key becomes a possible predecessor
    *    / \    \   otherwise go to left subtree or stop algo whem keys are equal
    *   1   3    15   
    *           /  \   
    *         11    16
    */
    t_node *predecessor = NULL;
    while (tree) {
        if (node->key < tree->key) tree = tree->leftPtr;
        if (node->key > tree->key) {
            predecessor = (t_node *)tree;
            tree = tree->rightPtr;
        }
        if (node->key == tree->key) break;
    }
    return predecessor;
}

/*
*       5
*      / \
*     2   10   for 5
*    / \    \   3 becomes successor
*   1   3    15   and 131 is the maximum in
*           /  \   the left subtree of 5
*         11    16
*/
t_node *predecessor(const t_node *node) {
    if (node->rightPtr) return maximum_chaining(node->leftPtr);
    /*
    *       5
    *      / \
    *     2   10   for 11 predecessor is the first node
    *    / \    \   that has the left child which is not 11
    *   1   3    15   
    *           /  \   
    *         11    16
    */
    t_node *y = node->parentPtr;
    while (y && node == y->leftPtr) {
        node = y;
        y = y->parentPtr;
    }
    return y;
}