#include <stdlib.h>
#include <stdio.h>

typedef struct Node Node;
struct Node {
    Node *next;
    void *data;
    int key;
};

typedef struct {
    Node *root;
} S_List;

void init(S_List **, int, const void *);
void insert(S_List *, int, const void *);
void delete(S_List *, int);
void *search(S_List *, int);
void iterate(S_List *, void(*)(void *, int));