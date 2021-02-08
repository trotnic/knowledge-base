#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdarg.h>

#include "list.h"

struct node {
    void *data;
    struct node *next;
    struct node *prev;    
};

struct list {
    struct node *head;
    struct node *tail;
    size_t count;
};

// UTIL

void init(t_list **list, void *data, size_t size, unsigned int amount) {
    *list = malloc(sizeof(t_list));
    if (!list) {
        error("NULL argument passed to a __%s__", __func__);
        return;
    }
    (*list)->count = 1;

    t_node *prev;
    for(size_t offset = 0; offset < amount; offset ++) {
        t_node *tmp = malloc(sizeof(t_node));
        tmp->data = malloc(size);
        memcpy(tmp->data, data + size * (offset), size);

        if (offset == 0) (*list)->head = tmp;
        else insert_node_after(*list, prev, tmp);

        prev = tmp;
    }
}

void iterate(const t_list *list, void(*handler)(void *)) {
    if (!list || !handler) {
        error("NULL argument passed to a __%s__", __func__);
        return;
    }
    t_node *tmp = list->head;

    while (tmp) {
        handler(tmp->data);
        tmp = tmp->next;
    }
}

size_t count(t_list *list) {
    return list ? list->count : 0;
}

bool isEmpty(t_list *list) {
    return !list->count;
}

// INSERT

bool insert_data_after(t_list *list, t_node *node, void *data) {
    if (!node) {
        error("NULL argument passed to a __%s__", __func__);
        return false;
    }
    t_node *new = malloc(sizeof(t_node));
    new->data = data;
    if (!new) {
        error("Can't insert data in __%s__", __func__);
        return false;
    }
    return insert_node_after(list, node, new);
}

bool insert_data_before(t_list *list, t_node *node, void *data) {
    if (!node) {
        error("NULL argument passed to a __%s__", __func__);
        return false;
    }
    t_node *new = malloc(sizeof(t_node));
    new->data = data;
    if (!new) {
        error("Can't insert data in __%s__", __func__);
        return false;
    }
    return insert_node_before(list, node, new);
}

bool insert_node_after(t_list *list, t_node *node, t_node *new) {
    if (!node || !new) {
        error("NULL argument passed to a __%s__", __func__);
        return false;
    }
    if (node->next) node->next->prev = new;

    new->next = node->next;
    node->next = new;
    new->prev = node;

    list->count++;
    return true;
}

bool insert_node_before(t_list *list, t_node *node, t_node *new) {
    if (!node || !new) {
        error("NULL argument passed to a __%s__", __func__);
        return false;
    }
    t_node *tmp = node->prev;
    node->prev = new;
    new->prev = tmp;

    tmp->next = new;
    new->next = node;

    list->count++;
    return true; 
}

// DELETE

void *delete_node_at(t_list *list, size_t position) {
    if (!list || position >= list->count) {
        error("Invalid arguments in __%s__", __func__);
        return NULL;
    }
    return delete_node(list, get_node_at(list, position));
}

void *delete_node(t_list *list, t_node *node) {
    if (node->prev) node->prev->next = node->next;

    if (node->next) node->next->prev = node->prev;

    if (list->head == node) list->head = node->next;

    void *data = node->data;
    free(node);
    list->count--;
    return data;
}

// GET

void *get_data_at(t_list *list, size_t position) {
    if (list && position < list->count) {
        t_node *result = get_node_at(list, position);
        return result ? result->data : NULL;
    }
    return NULL;
}

t_node *get_node_at(t_list *list, size_t position) {
    if (list && position < list->count) {
        size_t i = 0;

        t_node *tmp = list->head;
        while(tmp && i < position) {
            tmp = tmp->next;
            i++; 
        }
        return tmp;
    }

    return NULL;
}

// MAIN

void print_data(void *data) {
    printf("%d\t", *((int *)data));
}

int main(int argc, char const *argv[])
{

    int values[10];
    for (size_t i = 0; i < 10; i++) { 
        values[i] = rand() % 10 + 2;
        printf("%d\t", values[i]);
    }

    puts("");

    t_list *list;
    init(&list, values, sizeof(int), 10);
    

    delete_node(list, get_node_at(list, 5));
    printf("%d\n", *((int *)get_data_at(list, 5)));


    puts("");
    iterate(list, print_data);
    printf("\n%lu", list->count);
    
    return 0;
}
