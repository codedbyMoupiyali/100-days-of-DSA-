#include <stdio.h>
#include <stdlib.h>

int canPaint(int arr[], int n, int k, long long maxTime) {
    int painters = 1;
    long long curr = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > maxTime) return 0;

        if (curr + arr[i] > maxTime) {
            painters++;
            curr = arr[i];
            if (painters > k) return 0;
        } else {
            curr += arr[i];
        }
    }

    return 1;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *arr = (int *)malloc(n * sizeof(int));
    long long sum = 0, mx = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
        if (arr[i] > mx) mx = arr[i];
    }

    long long left = mx, right = sum, ans = sum;

    while (left <= right) {
        long long mid = left + (right - left) / 2;

        if (canPaint(arr, n, k, mid)) {
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