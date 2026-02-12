#include <stdio.h>

void reverse_array(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int temp;

    while (left < right) {
        // Swap elements at left and right pointers
        temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        // Move pointers toward the center
        left++;
        right--;
    }
}

int main() {
    int n, i;

    // Read size of array
    scanf("%d", &n);

    int arr[n];

    // Read array elements
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Reverse the array in-place
    reverse_array(arr, n);

    // Print the reversed array
    for (i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}