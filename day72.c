#include <stdio.h>
#include <string.h>

int main() {
    char s[100005];
    if (scanf("%100004s", s) != 1) return 0;

    int seen[256] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (seen[(unsigned char)s[i]]) {
            printf("%c\n", s[i]);
            return 0;
        }
        seen[(unsigned char)s[i]] = 1;
    }
    
    printf("-1\n");
    return 0;
}