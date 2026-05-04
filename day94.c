#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *arr = (int *)malloc(n * sizeof(int));
    int maxVal = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int *freq = (int *)calloc(maxVal + 1, sizeof(int));
    int *output = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        freq[i] += freq[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        output[freq[arr[i]] - 1] = arr[i];
        freq[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        printf("%d", output[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    free(arr);
    free(freq);
    free(output);

    return 0;
}