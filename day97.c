#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, end;
} Interval;

int compare(const void* a, const void* b) {
    return ((Interval*)a)->start - ((Interval*)b)->start;
}

void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

void push(int heap[], int* size, int val) {
    heap[++(*size)] = val;
    int i = *size;
    while (i > 1 && heap[i] < heap[i / 2]) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

void pop(int heap[], int* size) {
    heap[1] = heap[(*size)--];
    int i = 1;
    while (2 * i <= *size) {
        int child = 2 * i;
        if (child + 1 <= *size && heap[child + 1] < heap[child]) child++;
        if (heap[i] <= heap[child]) break;
        swap(&heap[i], &heap[child]);
        i = child;
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    Interval *intervals = malloc(n * sizeof(Interval));
    for (int i = 0; i < n; i++) scanf("%d %d", &intervals[i].start, &intervals[i].end);
    qsort(intervals, n, sizeof(Interval), compare);

    int *heap = malloc((n + 1) * sizeof(int));
    int heapSize = 0;
    push(heap, &heapSize, intervals[0].end);

    for (int i = 1; i < n; i++) {
        if (intervals[i].start >= heap[1]) pop(heap, &heapSize);
        push(heap, &heapSize, intervals[i].end);
    }

    printf("%d\n", heapSize);
    free(intervals); free(heap);
    return 0;
}