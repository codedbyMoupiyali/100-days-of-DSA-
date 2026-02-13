#include <stdio.h>

int main() {
    int m, n, i, j;

    scanf("%d %d", &m, &n);

    int a[m][n], b[m][n], result[m][n];

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &b[i][j]);

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            result[i][j] = a[i][j] + b[i][j];

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (j > 0) printf(" ");
            printf("%d", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}