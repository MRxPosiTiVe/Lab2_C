#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct StackNode {
    int data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
    int capacity; // v
    int size; // size <= capacity
};

void sAddElem(int value, struct Stack* stack); // +
int sPopElem(struct Stack* stack); // +
int sPeekElem(struct Stack* stack); // +
void initStack(struct Stack* stack, int capacity); // +
struct StackNode* sCreateElem(int data); // +


int main(void) {
    // It's a simple test for stack struct
    
    struct Stack stack;
    initStack(&stack, 3);
    sAddElem(10, &stack);
    sAddElem(13, &stack);
    sAddElem(18, &stack);

    sPeekElem(&stack);
    sPopElem(&stack);
    sAddElem(19, &stack);
    sAddElem(11, &stack);
    return 0;
}

void sAddElem(int value, struct Stack *stack) {
    if (stack->size + 1 > stack->capacity) {
        perror("Stack Overflow Exception");
        exit(EXIT_FAILURE);
    }
    struct StackNode *newNode = sCreateElem(value);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int sPopElem(struct Stack *stack) {
    if (stack->top == NULL) {
        perror("Stack is empty");
        exit(EXIT_FAILURE);
    }
    struct StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

int sPeekElem(struct Stack *stack) {
    if (stack->top == NULL) {
        perror("Stack is empty");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// *(pointer).hui = pointer->hui

void initStack(struct Stack *stack, int capacity)
{
    stack->top = NULL;
    stack->capacity = capacity;
}

struct StackNode *sCreateElem(int data)
{
    struct StackNode* newNode = malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
