#include <stdio.h>
#include <string.h>

void reverse(char str[], int left, int right) {
    char temp;

    if (left >= right)
        return;

    temp = str[left];
    str[left] = str[right];
    str[right] = temp;

    reverse(str, left + 1, right - 1);
}

int main() {
    char str[1000];

    scanf("%s", str);

    reverse(str, 0, strlen(str) - 1);

    printf("%s\n", str);

    return 0;
}