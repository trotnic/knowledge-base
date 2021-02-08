#include "../headers/types.h"

t_node *new(const void *data, const int key) {
    t_node *tree = malloc(sizeof(t_node));
    if (!tree) {
        error("Can't allocate memory for a tree in __%s__", __func__);
        return NULL;
    }
    tree->data      = (void *)data;
    tree->key       = key;
    tree->parentPtr = NULL;
    tree->leftPtr   = NULL;
    tree->rightPtr  = NULL;
    return tree;
}

void init(t_node **tree, const void *data, const int key) {
    *tree = malloc(sizeof(t_node));
    if (!(*tree)) {
        error("Can't allocate memory for a tree in %s", __func__);
        return;
    }
    (*tree)->data       = (void *)data;
    (*tree)->key        = key;
    (*tree)->parentPtr  = NULL;
    (*tree)->leftPtr    = NULL;
    (*tree)->rightPtr   = NULL;
}

void dealloc(t_node **tree) {
    if (!tree) {
        error("Can't deallocate NULL in __%s__", __func__);
        return;
    }
    free(*tree);
    *tree = NULL;
}

void *get_value(t_node *node) {
    return node->data;
}