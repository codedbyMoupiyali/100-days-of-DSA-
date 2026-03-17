#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (int*)malloc(capacity * sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

int isFull(PriorityQueue* pq) {
    return pq->size == pq->capacity;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue* pq, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (pq->data[index] < pq->data[parent]) {
            swap(&pq->data[index], &pq->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(PriorityQueue* pq, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        
        if (left < pq->size && pq->data[left] < pq->data[smallest]) {
            smallest = left;
        }
        
        if (right < pq->size && pq->data[right] < pq->data[smallest]) {
            smallest = right;
        }
        
        if (smallest != index) {
            swap(&pq->data[index], &pq->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void insert(PriorityQueue* pq, int value) {
    if (isFull(pq)) {
        pq->capacity *= 2;
        pq->data = (int*)realloc(pq->data, pq->capacity * sizeof(int));
    }
    
    pq->data[pq->size] = value;
    heapifyUp(pq, pq->size);
    pq->size++;
}

int delete(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        return -1;
    }
    
    int minValue = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    
    if (pq->size > 0) {
        heapifyDown(pq, 0);
    }
    
    return minValue;
}

int peek(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        return -1;
    }
    return pq->data[0];
}

void freePriorityQueue(PriorityQueue* pq) {
    free(pq->data);
    free(pq);
}

int main() {
    int n;
    scanf("%d", &n);
    
    PriorityQueue* pq = createPriorityQueue(n);
    
    for (int i = 0; i < n; i++) {
        char operation[20];
        scanf("%s", operation);
        
        if (strcmp(operation, "insert") == 0) {
            int value;
            scanf("%d", &value);
            insert(pq, value);
        } else if (strcmp(operation, "delete") == 0) {
            int result = delete(pq);
            printf("%d\n", result);
        } else if (strcmp(operation, "peek") == 0) {
            int result = peek(pq);
            printf("%d\n", result);
        }
    }
    
    freePriorityQueue(pq);
    
    return 0;
}