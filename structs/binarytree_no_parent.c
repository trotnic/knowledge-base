#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Node Node;
struct Node {
    int data;
    Node *leftPtr;
    Node *rightPtr;
};

Node *new(const int);
void init(Node **, const int);
void dealloc(Node **);
void insert(Node **, const int);
void delete(Node **, const int);

Node *search_chaining(const Node*, const int);
Node *search_iterating(const Node*, const int);

// O(h), h - height of a BST;
Node *minimum_iterating(const Node *);
Node *minimum_chaining(const Node *);
Node *maximum_iterating(const Node *);
Node *maximum_chaining(const Node *);

Node *successor_inorder(const Node *, const Node *);
Node *predecessor_inorder(const Node *, const Node *);

void inorder(Node *, void(*)(int));
void postorder(Node *, void(*)(int));
void preorder(Node *, void(*)(int));

void printing(int param) {
    printf("%d\n", param);
}

//           2
//          / \
//        1     5
//             / \
//            4   7
int main(int argc, char const *argv[])
{
    Node *node = new(2);
    insert(&node, 5);
    insert(&node, 1);
    insert(&node, 4);
    insert(&node, 7);

    printf("%d\n", predecessor_inorder(node, search_chaining(node, 4))->data);
    return 0;
}

// -

Node *new(const int value) {
    Node *tree = malloc(sizeof(Node));
    if (tree == NULL) {
        printf("Can't allocate memory for a tree in __%s__", __func__);
        return NULL;
    }
    tree->data = value;
    return tree;
}

 void init(Node **tree, const int value) {
    *tree = malloc(sizeof(Node));
    if (*tree == NULL) {
        printf("Can't allocate memory for a tree in %s", __func__);
        return;
    }
    (*tree)->leftPtr    = NULL;
    (*tree)->rightPtr   = NULL;
    (*tree)->data       = value;
}

void dealloc(Node **tree) {
    if (tree == NULL) {
        printf("Can't deallocate NULL in __%s__", __func__);
        return;
    }
    free(*tree);
    *tree = NULL;
}

// -

void insert(Node **tree, const int value) {
    if (tree == NULL) {
        printf("NULL pointer passed to a __%s__\n", __func__);
        return;
    }
    if (*tree == NULL) {
        *tree = malloc(sizeof(Node));
        if (*tree == NULL) {
            printf("Can't allocate memory for a node in __%s__", __func__);
            return;
        }
        
        (*tree)->data       = value;
        (*tree)->leftPtr    = NULL;
        (*tree)->rightPtr   = NULL;
        return;
    }
    if (value < (*tree)->data) {
        insert(&((*tree)->leftPtr), value);
    } else if (value > (*tree)->data) {
        insert(&((*tree)->rightPtr), value);
    } else {
        printf("Can't insert duplicate in a tree - %d\n__%s__", value, __func__);
    }
}

void delete(Node **tree, int value) {
    if (tree == NULL) {
        printf("NULL pointer passed to a __%s__\n", __func__);
        return;
    }
    // 1'st case - no children
    if ((*tree)->leftPtr == (*tree)->rightPtr == NULL) {

    }
}

// - 

Node *search_chaining(const Node *tree, const int value) {
    if (tree == NULL || tree->data == value) {
        return (Node *)tree;
    }
    return search_chaining(value < tree->data ? tree->leftPtr : tree->rightPtr, value);
}

Node *search_iterating(const Node *tree, const int value) {
    Node *ptr = (Node *)tree;
    while (ptr->data != value && ptr != NULL) {
        ptr = value < ptr->data ? ptr->leftPtr : ptr->rightPtr;
    }
    return ptr;
}

// -

Node *minimum_iterating(const Node *tree) {
    Node *ptr = (Node *)tree;
    while (ptr->leftPtr != NULL) {
        ptr = ptr->leftPtr;
    }
    return ptr;
}

Node *minimum_chaining(const Node *tree) {
    return tree->leftPtr == NULL ? (Node *)tree : minimum_chaining(tree->leftPtr);
}

Node *maximum_iterating(const Node *tree) {
    Node *ptr = (Node *)tree;
    while (ptr->rightPtr != NULL) {
        ptr = ptr->rightPtr;
    }
    return ptr;
}

Node *maximum_chaining(const Node *tree) {
    return tree->rightPtr == NULL ? (Node *)tree : maximum_chaining(tree->rightPtr);
}

// -

Node *successor_inorder(const Node *tree, const Node *node) {
    if (node->rightPtr != NULL) return minimum_chaining(node->rightPtr);

    Node *successor = NULL;
    while(tree != NULL) {
        if (node->data < tree->data) {
            successor = (Node *)tree;
            tree = tree->leftPtr;
        } 
        if (node->data > tree->data) tree = tree->rightPtr;
        if (node->data == tree->data) break; 
    }
    return successor;
}

Node *predecessor_inorder(const Node *tree, const Node *node) {
    if (node->leftPtr != NULL) return maximum_chaining(node->leftPtr);

    Node *predecessor = NULL;
    while (tree != NULL) {
        if (node->data < tree->data) tree = tree->leftPtr;
        if (node->data > tree->data) { 
            predecessor = (Node *)tree;
            tree = tree->rightPtr;
        }
        if (node->data == tree->data) break;
    }
    return predecessor;
}

// -

void inorder(Node *tree, void(*handler)(int)) {
    if (tree != NULL) {        
        inorder(tree->leftPtr, handler);
        handler(tree->data);
        inorder(tree->rightPtr, handler);
    }
}

void postorder(Node *tree, void(*handler)(int)) {
    if (tree != NULL) {
        postorder(tree->leftPtr, handler);
        postorder(tree->rightPtr, handler);
        handler(tree->data);
    }
}

void preorder(Node *tree, void(*handler)(int)) {
    if (tree != NULL) {
        handler(tree->data);
        preorder(tree->leftPtr, handler);
        preorder(tree->rightPtr, handler);
    }
}
