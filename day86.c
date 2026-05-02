#include <stdio.h>

int main() {
    long long n;
    if (scanf("%lld", &n) != 1) return 0;

    if (n < 2) {
        printf("%lld\n", n);
        return 0;
    }

    long long left = 0, right = n / 2, ans = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid * mid <= n) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%lld\n", ans);
    return 0;
}