#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct CircularQueue {
    struct Node* front;
    struct Node* rear;
    int size;
};

struct CircularQueue* createQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

int isEmpty(struct CircularQueue* queue) {
    return queue->front == NULL;
}

void enqueue(struct CircularQueue* queue, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
        newNode->next = newNode;
    } else {
        newNode->next = queue->front;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

int dequeue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    
    struct Node* temp = queue->front;
    int value = temp->data;
    
    if (queue->front == queue->rear) {
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
        queue->rear->next = queue->front;
    }
    
    free(temp);
    queue->size--;
    return value;
}

int peek(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    return queue->front->data;
}

void display(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    
    struct Node* current = queue->front;
    int count = 0;
    
    while (count < queue->size) {
        printf("%d", current->data);
        if (count < queue->size - 1) {
            printf(" ");
        }
        current = current->next;
        count++;
    }
    printf("\n");
}

void freeQueue(struct CircularQueue* queue) {
    if (!isEmpty(queue)) {
        struct Node* current = queue->front;
        struct Node* temp;
        
        queue->rear->next = NULL;
        
        while (current != NULL) {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(queue);
}

int main() {
    int n, m;
    
    scanf("%d", &n);
    
    struct CircularQueue* queue = createQueue();
    
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        enqueue(queue, value);
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        int dequeuedValue = dequeue(queue);
        if (dequeuedValue != -1) {
            enqueue(queue, dequeuedValue);
        }
    }
    
    display(queue);
    
    freeQueue(queue);
    
    return 0;
}