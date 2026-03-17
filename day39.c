#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int leftChild(int i) {
    return 2 * i + 1;
}

int rightChild(int i) {
    return 2 * i + 2;
}

void heapifyUp(MinHeap* heap, int index) {
    while (index > 0 && heap->data[parent(index)] > heap->data[index]) {
        swap(&heap->data[parent(index)], &heap->data[index]);
        index = parent(index);
    }
}

void heapifyDown(MinHeap* heap, int index) {
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void insert(MinHeap* heap, int value) {
    // Resize if needed
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    
    // Insert at the end
    heap->data[heap->size] = value;
    heap->size++;
    
    // Heapify up to maintain min-heap property
    heapifyUp(heap, heap->size - 1);
}

int extractMin(MinHeap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    
    int minValue = heap->data[0];
    
    // Move last element to root
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    // Heapify down to maintain min-heap property
    if (heap->size > 0) {
        heapifyDown(heap, 0);
    }
    
    return minValue;
}

int peek(MinHeap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    return heap->data[0];
}

int isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

int getSize(MinHeap* heap) {
    return heap->size;
}

void printHeap(MinHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void freeHeap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

int main() {
    int n;
    scanf("%d", &n);
    
    MinHeap* heap = createMinHeap(n);
    
    for (int i = 0; i < n; i++) {
        char operation[20];
        scanf("%s", operation);
        
        if (strcmp(operation, "insert") == 0) {
            int value;
            scanf("%d", &value);
            insert(heap, value);
        } else if (strcmp(operation, "extractMin") == 0) {
            int result = extractMin(heap);
            printf("%d\n", result);
        } else if (strcmp(operation, "peek") == 0) {
            int result = peek(heap);
            printf("%d\n", result);
        }
    }
    
    freeHeap(heap);
    
    return 0;
}