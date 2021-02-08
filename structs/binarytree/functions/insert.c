#include "../headers/types.h"

void insert(t_node **tree, const void *data, const int key) {
    t_node *y = NULL;
    t_node *x = (*tree);
    while (x) {
        y = x;
        x = key < x->key ? x->leftPtr : x->rightPtr;
    }
    t_node *parent = y;
    if (!y) {
        (*tree) = malloc(sizeof(t_node));
        (*tree)->key        = key;
        (*tree)->data       = (void *)data;
        (*tree)->parentPtr  = NULL;
        (*tree)->leftPtr    = NULL;
        (*tree)->rightPtr   = NULL;
    } else if (key < y->key) {
        y->leftPtr              = malloc(sizeof(t_node));
        y->leftPtr->key         = key;
        y->leftPtr->data        = (void *)data;
        y->leftPtr->parentPtr   = y;
        y->leftPtr->leftPtr     = NULL;
        y->leftPtr->rightPtr    = NULL;
    } else {
        y->rightPtr             = malloc(sizeof(t_node));
        y->rightPtr->key        = key;
        y->rightPtr->data       = (void *)data;
        y->rightPtr->parentPtr  = y;
        y->rightPtr->leftPtr    = NULL;
        y->rightPtr->rightPtr   = NULL;
    }
}