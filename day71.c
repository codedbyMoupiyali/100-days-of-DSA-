#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int m, n;
    if (scanf("%d", &m) != 1) return 0;
    if (scanf("%d", &n) != 1) return 0;

    int *table = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        table[i] = -1;
    }

    char op[10];
    int key;

    for (int k = 0; k < n; k++) {
        scanf("%s %d", op, &key);
        
        if (strcmp(op, "INSERT") == 0) {
            for (int i = 0; i < m; i++) {
                int idx = ((key % m) + i * i) % m;
                if (table[idx] == -1 || table[idx] == key) {
                    table[idx] = key;
                    break;
                }
            }
        } 
        else if (strcmp(op, "SEARCH") == 0) {
            int found = 0;
            for (int i = 0; i < m; i++) {
                int idx = ((key % m) + i * i) % m;
                if (table[idx] == key) {
                    found = 1;
                    break;
                }
                if (table[idx] == -1) {
                    break;
                }
            }
            if (found) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    free(table);
    return 0;
}