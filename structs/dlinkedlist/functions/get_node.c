#include "../headers/types.h"

void *get_data_at(t_list *list, size_t position) {
    if (list && position < count(list)) {
        t_node *result = get_node_at(list, position);
        return result ? result->data : NULL;
    }
    return NULL;
}

t_node *get_node_at(t_list *list, size_t position) {
    if (list && position < count(list)) {
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