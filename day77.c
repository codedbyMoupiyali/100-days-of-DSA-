#include <stdio.h>
#include <stdlib.h>

void dfs(int u, int n, int **adj, int *degree, int *visited) {
    visited[u] = 1;
    for (int i = 0; i < degree[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            dfs(v, n, adj, degree, visited);
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int **adj = (int **)malloc((n + 1) * sizeof(int *));
    int *degree = (int *)calloc(n + 1, sizeof(int));
    int *visited = (int *)calloc(n + 1, sizeof(int));
    
    int edge_list[m][2];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &edge_list[i][0], &edge_list[i][1]);
        degree[edge_list[i][0]]++;
        degree[edge_list[i][1]]++;
    }

    for (int i = 1; i <= n; i++) {
        adj[i] = (int *)malloc(degree[i] * sizeof(int));
    }

    int *temp_deg = (int *)calloc(n + 1, sizeof(int));
    for (int i = 0; i < m; i++) {
        int u = edge_list[i][0];
        int v = edge_list[i][1];
        adj[u][temp_deg[u]++] = v;
        adj[v][temp_deg[v]++] = u;
    }

    dfs(1, n, adj, degree, visited);

    int connected = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            connected = 0;
            break;
        }
    }

    if (connected) printf("CONNECTED\n");
    else printf("NOT CONNECTED\n");

    for (int i = 1; i <= n; i++) free(adj[i]);
    free(adj);
    free(degree);
    free(visited);
    free(temp_deg);

    return 0;
}