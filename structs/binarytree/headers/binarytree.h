#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct node t_node;

t_node *new(const void *, const int);
void init(t_node **, const void *, const int);
void dealloc(t_node **);
void *get_value(t_node *);

/*
* function pointer must return 1 in case when $1 < $2
* and 0 in case when $1 == $2
* But pretty nice to compare data, when we have keys 🙃
*/
// void insert(t_node **, const void *, _Bool(*)(const void*, const void*));
void insert(t_node **, const void *, const int);
void delete(t_node **, const int);

t_node *search_chaining(const t_node*, const int);
t_node *search_iterating(const t_node*, const int);

// O(h), h - height of a BST;
t_node *minimum_iterating(const t_node *);
t_node *minimum_chaining(const t_node *);
t_node *maximum_iterating(const t_node *);
t_node *maximum_chaining(const t_node *);

t_node *successor_inorder(const t_node *, const t_node *);
t_node *successor(const t_node *);
t_node *predecessor_inorder(const t_node *, const t_node *);
t_node *predecessor(const t_node *);

void inorder(t_node *, void(*)(void *, int));
void postorder(t_node *, void(*)(void *, int));
void preorder(t_node *, void(*)(void *, int));

#endif //BINARYTREE_BINARYTREE_H
