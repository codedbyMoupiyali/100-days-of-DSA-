#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int v, w;
    struct Edge* next;
};

void addEdge(struct Edge** head, int u, int v, int w) {
    struct Edge* newNode = (struct Edge*)malloc(sizeof(struct Edge));
    newNode->v = v;
    newNode->w = w;
    newNode->next = head[u];
    head[u] = newNode;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    struct Edge** head = (struct Edge**)calloc(n + 1, sizeof(struct Edge*));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(head, u, v, w);
        addEdge(head, v, u, w);
    }

    int* key = (int*)malloc((n + 1) * sizeof(int));
    int* inMST = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        key[i] = INT_MAX;
    }

    key[1] = 0;
    long long totalWeight = 0;

    for (int count = 0; count < n; count++) {
        int minKey = INT_MAX;
        int u = -1;

        for (int v = 1; v <= n; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break;

        inMST[u] = 1;
        totalWeight += minKey;

        struct Edge* temp = head[u];
        while (temp != NULL) {
            int v = temp->v;
            int w = temp->w;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
            }
            temp = temp->next;
        }
    }

    printf("%lld\n", totalWeight);

    for (int i = 1; i <= n; i++) {
        struct Edge* temp = head[i];
        while (temp != NULL) {
            struct Edge* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(head);
    free(key);
    free(inMST);

    return 0;
}