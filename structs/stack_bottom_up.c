#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct Stack {
     struct Node *bottom;
};

int main(int argc, char const *argv[])
{
    Stack *stack;
    int *data, i = 123, b = 352;
    data = &i;
    init(&stack, data);
    printf("%d\n", (*(int *)(peek(stack))));
    return 0;
}

void init(Stack **stack, const void *data) {
    if (data == NULL) {
        printf("NULL data passed to a __%s__", __func__);
        return;
    }
    *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Can't allocate memory for a stack in __%s__", __func__);
        return;
    }
    (*stack)->bottom = malloc(sizeof(Node));
    if ((*stack)->bottom == NULL) {
        puts("next NULL");
        return;
    }
    (*stack)->bottom->data = (void *)data;
    (*stack)->bottom->next = NULL;
}

void push(Stack *stack, const void *data) {
    if (stack == NULL || data == NULL) {
        printf("NULL argument passed to a __%s__", __func__);
        return;
    }
    Node *tmp = stack->bottom;
    while (tmp->next != NULL) tmp = tmp->next;     
    tmp->next = malloc(sizeof(Node));
    if (tmp->next == NULL) {
        printf("Can't allocate memory for a node in __%s__", __func__);
        return;
    }
    tmp->next->data = (void *)data;
    tmp->next->next = NULL;
}

void *pop(Stack *stack) {
    if (stack == NULL) {
        printf("NULL argument passed to a __%s__", __func__);
        return NULL;
    }
    Node *tmp = stack->bottom;
    if (tmp == NULL) {
        printf("Stack is empty in __%s__\n", __func__);
        return NULL;
    }
    Node *prev = NULL;
    while (tmp->next != NULL) { 
        prev = tmp;
        tmp = tmp->next;
    }
    if (stack->bottom == tmp) {
        void *data = stack->bottom->data;
        free(stack->bottom);
        stack->bottom = NULL;
        return data;
    } else {
        void *data = tmp->next->data;
        free(tmp->next);
        tmp->next = NULL;
        return data;
    }
}

void *peek(const Stack *stack) {
    if (stack == NULL) {
        printf("NULL argument passed to a __%s__", __func__);
        return NULL;
    }
    Node *tmp = stack->bottom;
    if (tmp == NULL) {
        printf("Stack is empty in __%s__\n", __func__);
        return NULL;
    }
    while (tmp->next != NULL) tmp = tmp->next;
    return tmp->data;
}