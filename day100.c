#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

void merge(Pair arr[], Pair temp[], int left, int mid, int right, int count[]) {
    int i = left;
    int j = mid + 1;
    int k = left;
    int smallerRight = 0;

    while (i <= mid && j <= right) {
        if (arr[i].value <= arr[j].value) {
            count[arr[i].index] += smallerRight;
            temp[k++] = arr[i++];
        } else {
            smallerRight++;
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        count[arr[i].index] += smallerRight;
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSort(Pair arr[], Pair temp[], int left, int right, int count[]) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid, count);
    mergeSort(arr, temp, mid + 1, right, count);
    merge(arr, temp, left, mid, right, count);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Pair *arr = (Pair *)malloc(n * sizeof(Pair));
    Pair *temp = (Pair *)malloc(n * sizeof(Pair));
    int *count = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
        arr[i].index = i;
    }

    mergeSort(arr, temp, 0, n - 1, count);

    for (int i = 0; i < n; i++) {
        printf("%d", count[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    free(arr);
    free(temp);
    free(count);
    return 0;
}