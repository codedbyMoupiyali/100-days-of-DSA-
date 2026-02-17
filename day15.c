#include <stdio.h>

int main() {
    int m, n, i, j, sum = 0;

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &m, &n);

    int matrix[m][n];

    printf("Enter the matrix elements row by row:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (i = 0; i < m && i < n; i++) {
        sum = sum + matrix[i][i];
    }

    printf("%d", sum);

    return 0;
}