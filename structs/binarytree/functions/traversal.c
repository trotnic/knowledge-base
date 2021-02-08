#include "../headers/types.h"

void inorder(t_node *tree, void(*handler)(void *, int)) {
    if (tree) {
        inorder(tree->leftPtr, handler);
        handler(tree->data, tree->key);
        inorder(tree->rightPtr, handler);
    }
}

void postorder(t_node *tree, void(*handler)(void *, int)) {
    if (tree) {
        postorder(tree->leftPtr, handler);
        postorder(tree->rightPtr, handler);
        handler(tree->data, tree->key);
    }
}

void preorder(t_node *tree, void(*handler)(void *, int)) {
    if (tree) {
        handler(tree->data, tree->key);
        preorder(tree->leftPtr, handler);
        preorder(tree->rightPtr, handler);
    }
}
