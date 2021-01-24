#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct Node Node;
struct Node {
    void *data;
    struct Node *next;
};

typedef struct {
    Node *top;
} Stack;

void init(Stack **, const void *);

void push(Stack *, const void *);
void *pop(Stack *);
void *peek(const Stack *);

int main(int argc, char const *argv[])
{
    int *data, value = 123;
    data = &value;
    Stack *stack;
    init(&stack, data);
    printf("%d\n", *((int *)peek(stack)));
    pop(stack);

    return 0;
}

void init(Stack **stack, const void *data) {
    if (data == NULL) {
        printf("NULL initial data passed in __%s__\n", __func__);
        return;
    }
    *stack = malloc(sizeof(Stack));
    if (*stack == NULL) {
        printf("Can't initialize a stack in __%s__\n", __func__);
        return;
    }
    (*stack)->top = malloc(sizeof(Node));
    if ((*stack)->top == NULL) {
        printf("Can't initialize a stack in __%s__\n", __func__);
        return;
    }
    (*stack)->top->next = NULL;
    (*stack)->top->data = (void *)data;
}

void push(Stack *stack, const void *data) {
    if (stack == NULL || data == NULL) {
        printf("NULL argument passed to a __%s__\n", __func__);
        return;
    }
    Node *tmp = stack->top;
    stack->top = malloc(sizeof(Node));
    if (stack->top == NULL) {
        printf("Can't allocate memory for a node in __%s__\n", __func__);
        stack->top = tmp;
        return;
    }
    stack->top->next = tmp;
    stack->top->data = (void *)data;
}

//  data is retrieved from the heap 
//  and requires to be freed from a memory
void *pop(Stack *stack) {
    if (stack == NULL) {
        printf("NULL argument passed to a __%s__\n", __func__);
        return NULL;
    }
    Node *tmp = stack->top;
    if (tmp == NULL) {
        printf("Stack is empty in __%s__\n", __func__);
        return NULL;
    }
    stack->top = tmp->next;
    void *result = tmp->data;
    free(tmp);
    return result;    
}

void *peek(const Stack *stack) {
    if (stack == NULL) {
        printf("NULL argument passed to a __%s__\n", __func__);
        return NULL;
    }
    if (stack->top == NULL) {
        printf("Stack is empty in __%s__\n", __func__);
        return NULL;
    }
    return stack->top->data;
}