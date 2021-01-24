#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    Node *next;
    int data;
};

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void init(Queue **queue, int value) {
    *queue = malloc(sizeof(Queue));
    if (queue == NULL) { 
        printf("Can't initialize a queue in %s\n", __func__);
        return; 
    }
    (*queue)->head = malloc(sizeof(Node));
    if ((*queue)->head == NULL) { 
        printf("Can't initialize queue's head in %s\n", __func__);
        return; 
    }

    (*queue)->head->data = value;
    (*queue)->tail = (*queue)->head;
}

bool isEmpty(Queue *queue) {
    return queue->head == NULL;
}

void enqueue(Queue **queue, int value) {
    if (queue == NULL) { 
        printf("Passed NULL to %s\n", __func__);
        return; 
    }

    Node *newPtr = malloc(sizeof(Node));
    if (newPtr == NULL) { 
        printf("Can't allocate memory for a node in %s\n", __func__);
        return; 
    }

    newPtr->data = value;
    newPtr->next = NULL;
    
    if (isEmpty(*queue)) {
        (*queue)->head = newPtr;
        (*queue)->tail = (*queue)->head;
    } else {
        newPtr->next = (*queue)->tail;
        (*queue)->tail = newPtr;
    }
}

int dequeue(Queue **queue) {
    if (queue == NULL) { 
        printf("Passed NULL to %s\n", __func__);
        return -1; 
    }
    Node *tmp = (*queue)->tail;
    printf("%p\n", tmp);
    while(tmp->next != (*queue)->head) {
        tmp = tmp->next;
    }
    
    int value = (*queue)->head->data;
    free((*queue)->head);
    (*queue)->head = tmp;
    tmp->next = NULL;
    return value;
}

int main(int argc, char const *argv[])
{
    Queue *queue;
    init(&queue, 532);
    enqueue(&queue, 123);
    printf("%d\n", dequeue(&queue));
    // printf("%d\n",queue->tail->data);
    // printf("%d\n",queue->head->data);
    return 0;
}
