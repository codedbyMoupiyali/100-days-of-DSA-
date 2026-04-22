#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct HeapNode {
    int vertex;
    int dist;
};

struct MinHeap {
    struct HeapNode* arr;
    int size;
    int capacity;
    int* pos;
};

struct Node* adj[MAX];
int V;

struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next   = NULL;
    return newNode;
}

void addEdge(int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = adj[u];
    adj[u]        = newNode;

    newNode       = createNode(u, w);
    newNode->next = adj[v];
    adj[v]        = newNode;
}

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap     = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->arr                = (struct HeapNode*)malloc(capacity * sizeof(struct HeapNode));
    heap->pos                = (int*)malloc(capacity * sizeof(int));
    heap->size               = 0;
    heap->capacity           = capacity;
    return heap;
}

void swapHeapNode(struct MinHeap* heap, int i, int j) {
    struct HeapNode temp = heap->arr[i];
    heap->arr[i]         = heap->arr[j];
    heap->arr[j]         = temp;

    heap->pos[heap->arr[i].vertex] = i;
    heap->pos[heap->arr[j].vertex] = j;
}

void minHeapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left     = 2 * idx + 1;
    int right    = 2 * idx + 2;

    if (left < heap->size && heap->arr[left].dist < heap->arr[smallest].dist)
        smallest = left;

    if (right < heap->size && heap->arr[right].dist < heap->arr[smallest].dist)
        smallest = right;

    if (smallest != idx) {
        swapHeapNode(heap, smallest, idx);
        minHeapify(heap, smallest);
    }
}

int isEmpty(struct MinHeap* heap) {
    return heap->size == 0;
}

struct HeapNode extractMin(struct MinHeap* heap) {
    struct HeapNode root  = heap->arr[0];
    struct HeapNode last  = heap->arr[heap->size - 1];

    heap->arr[0]          = last;
    heap->pos[root.vertex] = heap->size - 1;
    heap->pos[last.vertex] = 0;

    heap->size--;
    minHeapify(heap, 0);

    return root;
}

void decreaseKey(struct MinHeap* heap, int vertex, int dist) {
    int i            = heap->pos[vertex];
    heap->arr[i].dist = dist;

    while (i && heap->arr[i].dist < heap->arr[(i - 1) / 2].dist) {
        swapHeapNode(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

int inHeap(struct MinHeap* heap, int vertex) {
    return heap->pos[vertex] < heap->size;
}

void dijkstra(int src) {
    int dist[MAX];
    int parent[MAX];

    struct MinHeap* heap = createMinHeap(V);

    for (int v = 0; v < V; v++) {
        dist[v]           = INT_MAX;
        parent[v]         = -1;
        heap->arr[v].vertex = v;
        heap->arr[v].dist   = INT_MAX;
        heap->pos[v]        = v;
    }

    dist[src]            = 0;
    heap->arr[src].dist  = 0;
    heap->size           = V;

    decreaseKey(heap, src, 0);

    while (!isEmpty(heap)) {
        struct HeapNode minNode = extractMin(heap);
        int u                   = minNode.vertex;

        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (inHeap(heap, v) && dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v]   = dist[u] + w;
                parent[v] = u;
                decreaseKey(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    printf("\nVertex\t\tDistance from Source %d\t\tPath\n", src);
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < V; i++) {
        printf("  %d\t\t\t", i);

        if (dist[i] == INT_MAX)
            printf("UNREACHABLE\t\t\t");
        else
            printf("%d\t\t\t\t", dist[i]);

        if (dist[i] == INT_MAX) {
            printf("No Path");
        } else {
            int path[MAX], cnt = 0, cur = i;
            while (cur != -1) {
                path[cnt++] = cur;
                cur         = parent[cur];
            }
            for (int j = cnt - 1; j >= 0; j--) {
                if (j != 0) printf("%d -> ", path[j]);
                else        printf("%d", path[j]);
            }
        }
        printf("\n");
    }

    free(heap->arr);
    free(heap->pos);
    free(heap);
}

int main() {
    int E, u, v, w;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(src);

    return 0;
}