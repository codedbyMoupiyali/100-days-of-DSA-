#include <stdio.h>
#include <stdlib.h>

int isMinHeap(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[i] > arr[left])
            return 0;
        
        if (right < n && arr[i] > arr[right])
            return 0;
    }
    return 1;
}

int main() {
    int n, i;
    
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    if (isMinHeap(arr, n))
        printf("YES\n");
    else
        printf("NO\n");
    
    free(arr);
    
    return 0;
}