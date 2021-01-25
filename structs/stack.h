typedef struct Node Node;
struct Node {
    void *data;
    struct Node *next;
};

typedef struct Stack Stack;

void init(Stack **, const void *);

void push(Stack *, const void *);
void *pop(Stack *);
void *peek(const Stack *);