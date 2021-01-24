#include <stdio.h>
#include <stdlib.h>

struct Node {
    struct Node *next;
    int data;
};

typedef struct {
     struct Node *next;
} Stack;

void init(Stack **stack, int value) {
    *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        puts("stack NULL");
        return;
    }
    (*stack)->next = malloc(sizeof(struct Node));
    if ((*stack)->next == NULL) {
        puts("next NULL");
        return;
    }
    (*stack)->next->data = value;
    (*stack)->next->next = NULL;
}

void push(Stack **stack, int value) {
    if ((*stack)->next == NULL) {
        return;
    }
    struct Node *next = (*stack)->next;
    while (next->next != NULL) {
        next = next->next;
    }
    next->next = malloc(sizeof(struct Node));
    if (next->next == NULL) {
        return;
    }
    next->next->data = value;
    next->next->next = NULL;
}

int pop(Stack **stack) {
    if ((*stack) == NULL) {
        return -1;
    }
    struct Node *next = (*stack)->next;
    while (next->next->next != NULL) {
        next = next->next;
    }
    int value = next->next->data;
    free(next->next);
    next->next = NULL;
    return value;
}

int peek(Stack *stack) {
    if (stack->next == NULL) {
        return -1;
    }
    struct Node *next = stack->next;
    while (next->next != NULL) {
        next = next->next;
    }
    return next->data;
}

int main(int argc, char const *argv[])
{
    Stack *stack;
    init(&stack, 123);
    push(&stack, 421);
    printf("%d\n", peek(stack));
    pop(&stack);
    printf("%d\n", peek(stack));
    return 0;
}