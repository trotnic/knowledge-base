#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
struct Node {
    Node *next;
    int data;
    int key;
};

typedef struct {
    Node *root;
} S_List;

void init(S_List **list, int key, int value) {
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
    (*list)->root->data = value;
}

void insert(S_List **list, int key, int value) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    Node *tmp = (*list)->root;
    while (tmp->next != NULL) {
        if (tmp->key == key) {
            tmp->data = value;
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
    tmp->next->data = value;
}

void delete(S_List **list, int key) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    if ((*list)->root->key == key) {
        Node *tmp = (*list)->root->next;
        free((*list)->root);
        (*list)->root = tmp;
        return;
    }

    Node *prev = (*list)->root;
    Node *curr = (*list)->root;

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

int search(S_List *list, int key) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return -1;
    }
    Node *current = list->root;
    while (current != NULL)  {
        if (current->key == key) {
            return current->data;
        }
        current = current->next;
    }
    printf("No value for a key - %d\n", key);
    return -1;
}

void display(S_List **list) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    struct Node *tmp = (*list)->root;
    while (tmp != NULL) {
        printf("key - %d, value - %d\n", tmp->key, tmp->data);
        tmp = tmp->next;
    }
}

int main(int argc, char const *argv[])
{
    S_List *list;
    init(&list, 1, 12);
    insert(&list, 2, 235);
    insert(&list, 3, 735);
    insert(&list, 4, 935);
    insert(&list, 5, 535);
    delete(&list, 1);
    display(&list);
    return 0;
}
