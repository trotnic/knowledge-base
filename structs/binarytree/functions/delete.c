#include "../headers/types.h"

/*
* replaces in a `tree`
* node `u` with node `v`
*/
void transplant(t_node **tree, t_node *u, t_node *v) {
    /*
    * first three lines establish a connection in one way
    */
    if (!u->parentPtr) (*tree) = v;
    else if (u == u->parentPtr->leftPtr) u->parentPtr->leftPtr = v;
    else u->parentPtr->rightPtr = v;
    /*
    * the last line establishes a connection in another way
    */
    if (v) v->parentPtr = u->parentPtr;
    /*
    * works as <=>
    */
}

void delete(t_node **tree, const int key) {
    t_node *node = search_chaining(*tree, key);
    if (node == NULL) {
        printf("No such node for a key - %d", key);
        return;
    }
    if (!node->leftPtr) transplant(tree, node, node->rightPtr);
    else if (!node->rightPtr) transplant(tree, node, node->leftPtr);
    else {
        /*
        * finding a successor for a `node`
        */
        t_node *y = minimum_chaining(node->rightPtr);
        /*
        * in this case a successor is somewhere in a bottom of subtree and has own subtrees
        *
        *
        *       5
        *      / \
        *     2   12   deleting 12
        *        /  \
        *       9    17
        *           /
        *         15    15 replaces it
        *
        *       5
        *      / \
        *     2   15
        *        /  \
        *       9    17
        */
        if (y->parentPtr != node) {
            transplant(tree, y, y->rightPtr);
            y->rightPtr = node->rightPtr;
            y->rightPtr->parentPtr = y;
        }
        /*
        *
        *       5
        *      / \
        *     2   12   deleting 12
        *        /  \
        *       9    13   13 replaces it
        *
        *       5
        *      / \
        *     2   13
        *        /
        *       9
        */
        transplant(tree, node, y);
        y->leftPtr = node->leftPtr;
        y->leftPtr->parentPtr = y;
    }
}