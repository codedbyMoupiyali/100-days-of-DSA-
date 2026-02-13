#include <stdio.h>
#include <string.h>

int main() {
    char str[1000];
    int left, right, isPalindrome;

    scanf("%s", str);

    left = 0;
    right = strlen(str) - 1;
    isPalindrome = 1;

    while (left < right) {
        if (str[left] != str[right]) {
            isPalindrome = 0;
            break;
        }
        left++;
        right--;
    }

    if (isPalindrome)
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}