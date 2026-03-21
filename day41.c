#include <stdio.h>
#include <stdlib.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Queue structure with front and rear pointers
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Initialize queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

// Enqueue operation - add element to rear
void enqueue(struct Queue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        // Queue is empty
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue operation - remove element from front
int dequeue(struct Queue* q) {
    if (q->front == NULL) {
        // Queue is empty
        return -1;
    }
    
    struct Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    // If front becomes NULL, set rear to NULL too
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return value;
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Queue* q = createQueue();
    
    for (int i = 0; i < n; i++) {
        char operation[10];
        scanf("%s", operation);
        
        if (operation[0] == 'e' || operation[0] == 'E') {
            // Enqueue operation
            int value;
            scanf("%d", &value);
            enqueue(q, value);
        } else if (operation[0] == 'd' || operation[0] == 'D') {
            // Dequeue operation
            int result = dequeue(q);
            printf("%d\n", result);
        }
    }
    
    // Free remaining nodes
    while (q->front != NULL) {
        struct Node* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    free(q);
    
    return 0;
}