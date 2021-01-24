#include <stdlib.h>
#include <stdio.h>

// TODO: -

typedef struct Node Node;
struct Node {
    Node *next;
    Node *previous;
    int key;
    int data;
};

typedef struct {
    Node *root;
} D_List;

void init(D_List **list, int key, int value) {
    *list = malloc(sizeof(D_List));
    if (*list == NULL) {
        printf("Can't allocate memory for a list in %s", __func__);
        return;
    }
    (*list)->root = malloc(sizeof(Node));
    if ((*list)->root == NULL) {
        printf("Can't allocate memory for a node in %s", __func__);
        return;
    }
    (*list)->root->next     = NULL;
    (*list)->root->previous = NULL;
    (*list)->root->key      = key;
    (*list)->root->data     = value;
}

void insert(D_List **list, int key, int value) {
    if (list == NULL) {
        printf("NULL list ptr passed to %s", __func__);
        return;
    }
    // Node *current = (*list)->root;
    // while ()
}

int main(int argc, char const *argv[])
{
    D_List *list;
    return 0;
}
