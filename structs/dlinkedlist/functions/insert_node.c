#include "../headers/types.h"

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
    if (node->prev) node->prev->next = new;

    new->prev = node->prev;
    node->prev = new;
    new->next = node;

    if (node == list->head) list->head = new;

    list->count++;
    return true;
}