#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(int* arr, int n, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // Check if right child is larger than current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // If largest is not root, swap and continue heapifying
    if (largest != index) {
        swap(&arr[index], &arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

void buildMaxHeap(int* arr, int n) {
    // Start from last non-leaf node and heapify all nodes
    // Last non-leaf node is at index (n/2 - 1)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyDown(arr, n, i);
    }
}

void heapSort(int* arr, int n) {
    // Step 1: Build max heap
    buildMaxHeap(arr, n);
    
    // Step 2: Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum) to end
        swap(&arr[0], &arr[i]);
        
        // Heapify the reduced heap
        heapifyDown(arr, i, 0);
    }
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    printf("Original array: ");
    printArray(arr, n);
    
    heapSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    free(arr);
    
    return 0;
}