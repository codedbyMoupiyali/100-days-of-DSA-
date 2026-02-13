#include <stdio.h>

int main() {
    int r, c, i;

    scanf("%d %d", &r, &c);

    int matrix[r][c];

    for (i = 0; i < r; i++) {
        int j;
        for (j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    int top = 0, bottom = r - 1, left = 0, right = c - 1;
    int first = 1;

    while (top <= bottom && left <= right) {
        for (i = left; i <= right; i++) {
            if (!first) printf(" ");
            printf("%d", matrix[top][i]);
            first = 0;
        }
        top++;

        for (i = top; i <= bottom; i++) {
            if (!first) printf(" ");
            printf("%d", matrix[i][right]);
            first = 0;
        }
        right--;

        if (top <= bottom) {
            for (i = right; i >= left; i--) {
                if (!first) printf(" ");
                printf("%d", matrix[bottom][i]);
                first = 0;
            }
            bottom--;
        }

        if (left <= right) {
            for (i = bottom; i >= top; i--) {
                if (!first) printf(" ");
                printf("%d", matrix[i][left]);
                first = 0;
            }
            left++;
        }
    }

    return 0;
}