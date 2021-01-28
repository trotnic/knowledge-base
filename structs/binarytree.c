#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct Node Node;
struct Node {
    int key;
    void *data;
    Node *parentPtr;
    Node *leftPtr;
    Node *rightPtr;
};

Node *new(const void *, const int);
void init(Node **, const void *, const int);
void dealloc(Node **);

/*
* function pointer must return 1 in case when $1 < $2 
* and 0 in case when $1 == $2
* But pretty nice to compare data, when we have keys 🙃
*/
// void insert(Node **, const void *, _Bool(*)(const void*, const void*));
void insert(Node **, const void *, const int);
void delete(Node **, const int);

Node *search_chaining(const Node*, const int);
Node *search_iterating(const Node*, const int);

// O(h), h - height of a BST;
Node *minimum_iterating(const Node *);
Node *minimum_chaining(const Node *);
Node *maximum_iterating(const Node *);
Node *maximum_chaining(const Node *);

Node *successor_inorder(const Node *, const Node *);
Node *successor(const Node *);
Node *predecessor_inorder(const Node *, const Node *);
Node *predecessor(const Node *);

void inorder(Node *, void(*)(void *));
void postorder(Node *, void(*)(void *));
void preorder(Node *, void(*)(void *));

void printing(void *param) {
    printf("%d\n", *((int *)param));
}

/*
*           _
*           6
*          / \
*        1    12
*             / \
*            9   15
*           / \
*          7   10
*          -

*  after deleting 6
*  element 7 replaces it 
*  as the successor

*          7
*         / \
*        1   12
*           /  \
*          9    15
*           \
*            10
*/

int main(int argc, char const *argv[])
{
    int *data, i = 123;
    data = &i;
    Node *node = new(data, 1);   
    insert(&node, data, 4);
    insert(&node, data, 5);
    insert(&node, data, 2);

    printf("%d\n", successor(search_chaining(node, 2))->key);
    return 0;
}

// -

Node *new(const void *data, const int key) {
    Node *tree = malloc(sizeof(Node));
    if (tree == NULL) {
        printf("Can't allocate memory for a tree in __%s__", __func__);
        return NULL;
    }
    tree->data      = (void *)data;
    tree->key       = key;
    tree->parentPtr = NULL;
    tree->leftPtr   = NULL;
    tree->rightPtr  = NULL;
    return tree;
}

void init(Node **tree, const void *data, const int key) {
    *tree = malloc(sizeof(Node));
    if (*tree == NULL) {
        printf("Can't allocate memory for a tree in %s", __func__);
        return;
    }
    (*tree)->data       = (void *)data;
    (*tree)->key        = key;
    (*tree)->parentPtr  = NULL;
    (*tree)->leftPtr    = NULL;
    (*tree)->rightPtr   = NULL;
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

Node *search_chaining(const Node *tree, const int key) {
    if (tree == NULL || tree->key == key) {
        return (Node *)tree;
    }
    return search_chaining(key < tree->key ? tree->leftPtr : tree->rightPtr, key);
}

Node *search_iterating(const Node *tree, const int key) {
    Node *ptr = (Node *)tree;
    while (ptr->key != key && ptr != NULL) {
        ptr = key < ptr->key ? ptr->leftPtr : ptr->rightPtr;
    }
    return ptr;
}

// -

// void insert(Node **tree, const void *data, _Bool(*comparator)(const void*, const void*)) {
//     if (tree == NULL) {
//         printf("NULL pointer passed to a __%s__\n", __func__);
//         return;
//     }
//     if (*tree == NULL) {
//         *tree = malloc(sizeof(Node));
//         if (*tree == NULL) {
//             printf("Can't allocate memory for a node in __%s__", __func__);
//             return;
//         }
        
//         (*tree)->data       = (void *)data;
//         (*tree)->parentPtr  = NULL;
//         (*tree)->leftPtr    = NULL;
//         (*tree)->rightPtr   = NULL;
//         return;
//     }
//     if (comparator(data, (*tree)->data)) {
//         insert(&((*tree)->leftPtr), data, comparator);
//     } else if (comparator((*tree)->data, data)) {
//         insert(&((*tree)->rightPtr), data, comparator);
//     } else {
//         printf("Can't insert duplicate in a tree - %p\n__%s__", data, __func__);
//     }
// }

void insert(Node **tree, const void *data, const int key) {
    Node *y = NULL;
    Node *x = (*tree);
    while (x != NULL) {
        y = x;
        x = key < x->key ? x->leftPtr : x->rightPtr;
    }
    Node *parent = y;
    if (y == NULL) {
        (*tree) = malloc(sizeof(Node));
        (*tree)->key        = key;
        (*tree)->data       = (void *)data;
        (*tree)->parentPtr  = NULL;
        (*tree)->leftPtr    = NULL;
        (*tree)->rightPtr   = NULL;
    } else if (key < y->key) {
        y->leftPtr              = malloc(sizeof(Node));
        y->leftPtr->key         = key;
        y->leftPtr->data        = (void *)data;
        y->leftPtr->parentPtr   = y;
        y->leftPtr->leftPtr     = NULL;
        y->leftPtr->rightPtr    = NULL;
    } else {
        y->rightPtr             = malloc(sizeof(Node));
        y->rightPtr->key        = key;
        y->rightPtr->data       = (void *)data;
        y->rightPtr->parentPtr  = y;
        y->rightPtr->leftPtr    = NULL;
        y->rightPtr->rightPtr   = NULL;
    }
}

/*
* replaces in a `tree` 
* node `u` with node `v`
*/
void transplant(Node **tree, Node *u, Node *v) {
    /*
    * first three lines establish a connection in one way
    */
    if (u->parentPtr == NULL) (*tree) = v;
    else if (u == u->parentPtr->leftPtr) u->parentPtr->leftPtr = v;
    else u->parentPtr->rightPtr = v;
    /*
    * the last line establishes a connection in another way
    */
    if (v != NULL) v->parentPtr = u->parentPtr;
    /*
    * works as <=>
    */
}

void delete(Node **tree, const int key) {
    Node *node = search_chaining(*tree, key);
    if (node == NULL) {
        printf("No such node for a key - %d", key);
        return;
    }
    if (node->leftPtr == NULL) {
        transplant(tree, node, node->rightPtr);
    } else if (node->rightPtr == NULL) {
        transplant(tree, node, node->leftPtr);
    } else {
        /*
        * finding a successor for a `node`
        */
        Node *y = minimum_chaining(node->rightPtr);
        /*
        * in this case a successor is somewhere in a bottom of subtree and has own subtrees
        * 
        * 
        *       5
        *      / \
        *     2   12   deleting 12
        *        /  \
        *       9    17
        *           /
        *         15    15 replaces it
        * 
        *       5
        *      / \
        *     2   15
        *        /  \
        *       9    17
        */
        if (y->parentPtr != node) {
            transplant(tree, y, y->rightPtr);
            y->rightPtr = node->rightPtr;
            y->rightPtr->parentPtr = y;
        }
        /*
        *
        *       5
        *      / \
        *     2   12   deleting 12 
        *        /  \
        *       9    13   13 replaces it
        * 
        *       5
        *      / \
        *     2   13
        *        /
        *       9
        */
        transplant(tree, node, y);
        y->leftPtr = node->leftPtr;
        y->leftPtr->parentPtr = y;
    }
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

    /*
    *       5
    *      / \
    *     2   10   for 10 
    *    / \    \   11 becomes successor 
    *   1   3    15   and 11 is the minimum in 
    *           /  \   the right subtree of 10
    *         11    16
    */
Node *successor_inorder(const Node *tree, const Node *node) {
    if (node->rightPtr != NULL) return minimum_chaining(node->rightPtr);
    /*      _
    *       5   for a 3 search begins from a root
    *      / \   so when a current key is greater than 3
    *     2   10   then this key becomes a possible successor
    *    / \    \   otherwise go to right subtree or stop algo whem keys are equal
    *   1   3    15   
    *       -   /  \   
    *         11    16
    */
    Node *successor = NULL;
    while(tree != NULL) {
        if (node->key < tree->key) {
            successor = (Node *)tree;
            tree = tree->leftPtr;
        } 
        if (node->key > tree->key) tree = tree->rightPtr;
        if (node->key == tree->key) break; 
    }
    return successor;
}

    /*
    *       5
    *      / \
    *     2   10   for 10 
    *    / \    \   11 becomes successor 
    *   1   3    15   and 11 is the minimum in 
    *           /  \   the right subtree of 10
    *         11    16
    */
Node *successor(const Node *node) {
    if (node->rightPtr != NULL) return minimum_chaining(node->rightPtr);
    /*
    *       5
    *      / \
    *     2   10   for 3 successor is the first node
    *    / \    \   that has the right child which is not 3
    *   1   3    15   
    *           /  \   
    *         11    16
    */
    Node *y = node->parentPtr;
    while (y != NULL && node == y->rightPtr) {
        node = y;
        y = y->parentPtr;
    }
    return y;
}


   /*
    *       5
    *      / \
    *     2   10   for 5 
    *    / \    \   3 becomes predecessor 
    *   1   3    15   and 3 is the maximum in 
    *           /  \   the left subtree of 5
    *         11    16
    */
Node *predecessor_inorder(const Node *tree, const Node *node) {
    if (node->leftPtr != NULL) return maximum_chaining(node->leftPtr);
    /*      
    *       5   for a 10 search begins from a root
    *      / \   so when a current key is less than 10
    *     2   10   then this key becomes a possible predecessor
    *    / \    \   otherwise go to left subtree or stop algo whem keys are equal
    *   1   3    15   
    *           /  \   
    *         11    16
    */
    Node *predecessor = NULL;
    while (tree != NULL) {
        if (node->key < tree->key) tree = tree->leftPtr;
        if (node->key > tree->key) { 
            predecessor = (Node *)tree;
            tree = tree->rightPtr;
        }
        if (node->key == tree->key) break;
    }
    return predecessor;
}

    /*
    *       5
    *      / \
    *     2   10   for 5 
    *    / \    \   3 becomes successor 
    *   1   3    15   and 131 is the maximum in 
    *           /  \   the left subtree of 5
    *         11    16
    */
Node *predecessor(const Node *node) {
    if (node->rightPtr != NULL) return maximum_chaining(node->leftPtr);
    /*
    *       5
    *      / \
    *     2   10   for 11 predecessor is the first node
    *    / \    \   that has the left child which is not 11
    *   1   3    15   
    *           /  \   
    *         11    16
    */
    Node *y = node->parentPtr;
    while (y != NULL && node == y->leftPtr) {
        node = y;
        y = y->parentPtr;
    }
    return y;
}

// -

void inorder(Node *tree, void(*handler)(void *)) {
    if (tree != NULL) {        
        inorder(tree->leftPtr, handler);
        handler(tree->data);
        inorder(tree->rightPtr, handler);
    }
}

void postorder(Node *tree, void(*handler)(void *)) {
    if (tree != NULL) {
        postorder(tree->leftPtr, handler);
        postorder(tree->rightPtr, handler);
        handler(tree->data);
    }
}

void preorder(Node *tree, void(*handler)(void *)) {
    if (tree != NULL) {
        handler(tree->data);
        preorder(tree->leftPtr, handler);
        preorder(tree->rightPtr, handler);
    }
}
