#include <stdio.h>

int main() {
    int m, n, i, j, flag = 1;

    scanf("%d %d", &m, &n);

    int matrix[m][n];

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if (m != n) {
        flag = 0;
    } else {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                break;
        }
    }

    if (flag == 1)
        printf("Symmetric Matrix");
    else
        printf("Not a Symmetric Matrix");

    return 0;
}