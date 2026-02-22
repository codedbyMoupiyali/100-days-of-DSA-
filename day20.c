#include <stdio.h>

int main() {
    int n, i, j, k;

    printf("Enter the size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the array elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int count = 0;

    for (i = 0; i < n; i++) {
        int sum = 0;
        for (j = i; j < n; j++) {
            sum = sum + arr[j];
            if (sum == 0) {
                count++;
            }
        }
    }

    printf("%d", count);

    return 0;
}