#include <stdio.h>

int main() {
    int n, i, j;

    printf("Enter the size of array: ");
    scanf("%d", &n);

    int arr[n];
    int count[n];
    int visited[n];

    printf("Enter the array elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        count[i] = 0;
        visited[i] = 0;
    }

    for (i = 0; i < n; i++) {
        if (visited[i] == 1)
            continue;

        count[i] = 1;
        for (j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count[i]++;
                visited[j] = 1;
            }
        }
    }

    int first = 1;
    for (i = 0; i < n; i++) {
        if (visited[i] == 0) {
            if (first == 1) {
                printf("%d:%d", arr[i], count[i]);
                first = 0;
            } else {
                printf(" %d:%d", arr[i], count[i]);
            }
        }
    }

    return 0;
}