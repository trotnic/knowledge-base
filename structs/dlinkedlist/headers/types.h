#ifndef DLINKEDLIST_TYPES_H
#define DLINKEDLIST_TYPES_H

#include <stdlib.h>
#include <memory.h>
#include "../util/error.h"
#include "../headers/list.h"

struct node {
    void *data;
    struct node *next;
    struct node *prev;
};

struct list {
    struct node *head;
    size_t count;
};

#endif //DLINKEDLIST_TYPES_H
