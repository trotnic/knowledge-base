#ifndef BINARYTREE_TYPES_H
#define BINARYTREE_TYPES_H

#include <memory.h>
#include <stdlib.h>
#include "../util/error.h"
#include "../headers/binarytree.h"

typedef struct node t_node;
struct node {
    int key;
    void *data;
    struct node *parentPtr;
    struct node *leftPtr;
    struct node *rightPtr;
};

#endif //BINARYTREE_TYPES_H
