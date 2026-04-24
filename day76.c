#include <stdio.h>
#include <stdlib.h>

void dfs(int u, int n, int adj[n + 1][n + 1], int visited[]) {
    visited[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v, n, adj, visited);
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int (*adj)[n + 1] = calloc((n + 1) * (n + 1), sizeof(int));
    int *visited = calloc(n + 1, sizeof(int));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            count++;
            dfs(i, n, adj, visited);
        }
    }

    printf("%d\n", count);

    free(adj);
    free(visited);
    return 0;
}