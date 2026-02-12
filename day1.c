#include <stdio.h>

int main() {
    int n;

    scanf("%d", &n);

    int arr[n + 1];


    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pos;
    scanf("%d", &pos);

  
    int x;
    scanf("%d", &x);

    for (int i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos - 1] = x;

    for (int i = 0; i <= n; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}