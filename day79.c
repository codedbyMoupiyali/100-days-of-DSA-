#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    long long dist;
    int node;
} HeapNode;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

void push(HeapNode heap[], int *size, long long dist, int node) {
    int i = ++(*size);
    heap[i].dist = dist;
    heap[i].node = node;

    while (i > 1 && heap[i].dist < heap[i / 2].dist) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

HeapNode pop(HeapNode heap[], int *size) {
    HeapNode top = heap[1];
    heap[1] = heap[(*size)--];

    int i = 1;
    while (1) {
        int left = 2 * i;
        int right = 2 * i + 1;
        int smallest = i;

        if (left <= *size && heap[left].dist < heap[smallest].dist) {
            smallest = left;
        }
        if (right <= *size && heap[right].dist < heap[smallest].dist) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return top;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *head = (int *)malloc((n + 1) * sizeof(int));
    Edge *edges = (Edge *)malloc(m * sizeof(Edge));
    long long *dist = (long long *)malloc((n + 1) * sizeof(long long));
    HeapNode *heap = (HeapNode *)malloc((m + n + 5) * sizeof(HeapNode));

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dist[i] = LLONG_MAX;
    }

    int edgeCount = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[edgeCount].to = v;
        edges[edgeCount].weight = w;
        edges[edgeCount].next = head[u];
        head[u] = edgeCount++;
    }

    int source;
    scanf("%d", &source);

    int heapSize = 0;
    dist[source] = 0;
    push(heap, &heapSize, 0, source);

    while (heapSize > 0) {
        HeapNode cur = pop(heap, &heapSize);
        long long d = cur.dist;
        int u = cur.node;

        if (d != dist[u]) {
            continue;
        }

        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            int w = edges[i].weight;

            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push(heap, &heapSize, dist[v], v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dist[i] == LLONG_MAX) {
            printf("INF");
        } else {
            printf("%lld", dist[i]);
        }
        if (i < n) {
            printf(" ");
        }
    }
    printf("\n");

    free(head);
    free(edges);
    free(dist);
    free(heap);

    return 0;
}