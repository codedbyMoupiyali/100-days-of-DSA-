#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Interval;

int compare(const void* a, const void* b) {
    Interval* i1 = (Interval*)a;
    Interval* i2 = (Interval*)b;
    if (i1->start != i2->start) return i1->start - i2->start;
    return i1->end - i2->end;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    if (n == 0) return 0;

    Interval* arr = malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    qsort(arr, n, sizeof(Interval), compare);

    Interval* merged = malloc(n * sizeof(Interval));
    int k = 0;
    merged[k] = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i].start <= merged[k].end) {
            if (arr[i].end > merged[k].end) {
                merged[k].end = arr[i].end;
            }
        } else {
            k++;
            merged[k] = arr[i];
        }
    }

    for (int i = 0; i <= k; i++) {
        printf("%d %d\n", merged[i].start, merged[i].end);
    }

    free(arr);
    free(merged);
    return 0;
}