#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    long long dist[n][n];
    long long INF = 1000000000000000LL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long x;
            scanf("%lld", &x);
            if (i == j) dist[i][j] = 0;
            else if (x == -1) dist[i][j] = INF;
            else dist[i][j] = x;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) printf("-1");
            else printf("%lld", dist[i][j]);
            if (j < n - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}