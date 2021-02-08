#include "../headers/types.h"

t_node *minimum_iterating(const t_node *tree) {
    t_node *ptr = (t_node *)tree;
    while (ptr->leftPtr) ptr = ptr->leftPtr;
    return ptr;
}

t_node *minimum_chaining(const t_node *tree) {
    return tree->leftPtr ? minimum_chaining(tree->leftPtr) : (t_node *)tree;
}

t_node *maximum_iterating(const t_node *tree) {
    t_node *ptr = (t_node *)tree;
    while (ptr->rightPtr) ptr = ptr->rightPtr;
    return ptr;
}

t_node *maximum_chaining(const t_node *tree) {
    return tree->rightPtr ? maximum_chaining(tree->rightPtr) : (t_node *)tree;
}