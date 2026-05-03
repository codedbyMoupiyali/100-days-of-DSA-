#include <stdio.h>
#include <stdlib.h>

int canAllocate(int arr[], int n, int m, long long maxPages) {
    int students = 1;
    long long pages = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > maxPages) return 0;

        if (pages + arr[i] > maxPages) {
            students++;
            pages = arr[i];
            if (students > m) return 0;
        } else {
            pages += arr[i];
        }
    }

    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *arr = (int *)malloc(n * sizeof(int));
    long long sum = 0, mx = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
        if (arr[i] > mx) mx = arr[i];
    }

    if (m > n) {
        printf("-1\n");
        free(arr);
        return 0;
    }

    long long left = mx, right = sum, ans = sum;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (canAllocate(arr, n, m, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%lld\n", ans);

    free(arr);
    return 0;
}