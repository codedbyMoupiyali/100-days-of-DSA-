#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int min_sum = abs(arr[0] + arr[1]);
    int num1 = arr[0], num2 = arr[1];

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int current_sum = abs(arr[i] + arr[j]);
            if (current_sum < min_sum) {
                min_sum = current_sum;
                num1 = arr[i];
                num2 = arr[j];
            }
        }
    }

    if (num1 > num2) {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }

    printf("%d %d\n", num1, num2);

    return 0;
}