#include <stdio.h>

int main() {
    int n, i, j;

    scanf("%d", &n);
    int arr[n];
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    if (n == 0) {
        printf("\n");
        return 0;
    }

    j = 0;

    for (i = 1; i < n; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }

    for (i = 0; i <= j; i++) {
        if (i > 0) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}