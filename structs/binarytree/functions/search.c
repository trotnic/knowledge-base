#include "../headers/types.h"

t_node *search_chaining(const t_node *tree, const int key) {
    if (!tree || tree->key == key) {
        return (t_node *)tree;
    }
    return search_chaining(key < tree->key ? tree->leftPtr : tree->rightPtr, key);
}

t_node *search_iterating(const t_node *tree, const int key) {
    t_node *ptr = (t_node *)tree;
    while (ptr->key != key && ptr) {
        ptr = key < ptr->key ? ptr->leftPtr : ptr->rightPtr;
    }
    return ptr;
}