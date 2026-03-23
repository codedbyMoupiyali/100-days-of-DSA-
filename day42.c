#include <stdio.h>
#include <stdlib.h>

struct StackNode {
    int data;
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

int isStackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

void push(struct Stack* stack, int value) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        return -1;
    }
    struct StackNode* temp = stack->top;
    int value = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

struct QueueNode {
    int data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

void enqueue(struct Queue* queue, int value) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = value;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }
    struct QueueNode* temp = queue->front;
    int value = temp->data;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return value;
}

void reverseQueue(struct Queue* queue) {
    struct Stack* stack = createStack();
    
    while (!isQueueEmpty(queue)) {
        push(stack, dequeue(queue));
    }
    
    while (!isStackEmpty(stack)) {
        enqueue(queue, pop(stack));
    }
    
    free(stack);
}

void printQueue(struct Queue* queue) {
    struct QueueNode* temp = queue->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Queue* queue = createQueue();
    
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        enqueue(queue, value);
    }
    
    reverseQueue(queue);
    
    printQueue(queue);
    
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
    
    return 0;
}