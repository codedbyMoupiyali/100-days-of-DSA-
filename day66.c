#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    bool* visited;
    bool* recStack;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(bool));
    graph->recStack = malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
        graph->recStack[i] = false;
    }
    return graph;
}

void addEdge(struct Graph* graph, int s, int d) {
    struct Node* newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
}

bool isCyclicUtil(struct Graph* graph, int v) {
    if (!graph->visited[v]) {
        graph->visited[v] = true;
        graph->recStack[v] = true;

        struct Node* temp = graph->adjLists[v];
        while (temp) {
            int adjV = temp->vertex;
            if (!graph->visited[adjV] && isCyclicUtil(graph, adjV))
                return true;
            else if (graph->recStack[adjV])
                return true;
            temp = temp->next;
        }
    }
    graph->recStack[v] = false;
    return false;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    struct Graph* graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    bool hasCycle = false;
    for (int i = 0; i < n; i++) {
        if (isCyclicUtil(graph, i)) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle) printf("YES\n");
    else printf("NO\n");

    return 0;
}