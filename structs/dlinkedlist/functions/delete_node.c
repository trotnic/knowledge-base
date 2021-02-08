#include "../headers/types.h"

void *delete_node_at(t_list *list, size_t position) {
    if (!list || position >= count(list)) {
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