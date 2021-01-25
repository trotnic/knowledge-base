#include "slinkedlist.h"

void init(S_List **list, int key, const void *data) {
    *list = malloc(sizeof(S_List));
    if (list == NULL) {
        printf("Can't allocate memory for a list in %s", __func__);
        return;
    }
    (*list)->root = malloc(sizeof(Node));
    if ((*list)->root == NULL) {
        printf("Can't allocate memory for a node in %s", __func__);
        return;
    }
    (*list)->root->next = NULL;
    (*list)->root->key = key;
    (*list)->root->data = (void *)data;
}

void insert(S_List *list, int key, const void *data) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    Node *tmp = list->root;
    while (tmp->next != NULL) {
        if (tmp->key == key) {
            tmp->data = (void *)data;
            return;
        }
        tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(Node));
    if (tmp->next == NULL) {
        printf("Can't allocate memory for a node in %s", __func__);
        return;
    }
    tmp->next->next = NULL;
    tmp->next->key = key;
    tmp->next->data = (void *)data;
}

void delete(S_List *list, int key) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    if (list->root->key == key) {
        Node *tmp = list->root->next;
        free(list->root);
        list->root = tmp;
        return;
    }

    Node *prev = list->root;
    Node *curr = list->root;

    while (curr != NULL) {
        if (curr->key == key) {
            prev->next = curr->next;
            free(curr);
            return;
        }        
        prev = curr;
        curr = curr->next;
    }
    printf("No such key to delete - %d\n", key);
}

void *search(S_List *list, int key) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return NULL;
    }
    Node *current = list->root;
    while (current != NULL)  {
        if (current->key == key) {
            return current->data;
        }
        current = current->next;
    }
    printf("No value for a key - %d\n", key);
    return NULL;
}

void iterate(S_List *list, void(*handler)(void *, int)) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    struct Node *tmp = list->root;
    while (tmp != NULL) {
        handler(tmp->data, tmp->key);
        tmp = tmp->next;
    }
}

// -

void displayInt(void *obj, int key) {    
    printf("key - %d, value - %d\n", key, (*(int *)obj));
}

int main(int argc, char const *argv[])
{
    S_List *list;
    int a = 12, b = 235, c = 735, d = 935;
    init(&list, 1, &a);
    insert(list, 2, &b);
    insert(list, 3, &c);
    insert(list, 4, &d);
    delete(list, 1);
    iterate(list, displayInt);
    return 0;
}
