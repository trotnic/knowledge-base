#include "../headers/types.h"

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