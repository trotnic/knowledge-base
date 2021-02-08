#ifndef DLINKEDLIST_LIST_H
#define DLINKEDLIST_LIST_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct node t_node;
typedef struct list t_list;

void iterate(const t_list *, void(*)(void *));
void init(t_list **, void *, size_t, unsigned int);
size_t count(t_list *);
bool isEmpty(t_list *);

// INSERT

bool insert_data_after(t_list *, t_node *, void *);
bool insert_data_before(t_list *, t_node *, void *);

bool insert_node_after(t_list *, t_node *, t_node *);
bool insert_node_before(t_list *, t_node *, t_node *);

// DELETE

void *delete_node_at(t_list *, size_t);
void *delete_node(t_list *, t_node *);

// GET

void *get_data_at(t_list *, size_t);

t_node *get_node_at(t_list *, size_t);

#endif //DLINKEDLIST_LIST_H
