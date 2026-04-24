#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long sum;
    int index;
} Prefix;

int compare(const void *a, const void *b) {
    Prefix *pa = (Prefix *)a;
    Prefix *pb = (Prefix *)b;
    if (pa->sum < pb->sum) return -1;
    if (pa->sum > pb->sum) return 1;
    return pa->index - pb->index;
}

int main() {
    int arr[100005];
    int n = 0;
    
    while (scanf("%d", &arr[n]) == 1) {
        n++;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    Prefix *p = (Prefix *)malloc((n + 1) * sizeof(Prefix));
    p[0].sum = 0;
    p[0].index = -1;
    
    long long current_sum = 0;
    for (int i = 0; i < n; i++) {
        current_sum += arr[i];
        p[i + 1].sum = current_sum;
        p[i + 1].index = i;
    }

    qsort(p, n + 1, sizeof(Prefix), compare);

    int max_len = 0;
    int min_idx = p[0].index;

    for (int i = 1; i <= n; i++) {
        if (p[i].sum == p[i - 1].sum) {
            int len = p[i].index - min_idx;
            if (len > max_len) {
                max_len = len;
            }
        } else {
            min_idx = p[i].index;
        }
    }

    printf("%d\n", max_len);

    free(p);
    return 0;
}