#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char (*votes)[105] = malloc(n * sizeof(*votes));
    if (!votes) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%104s", votes[i]);
    }

    qsort(votes, n, sizeof(votes[0]), compare);

    int max_votes = 0;
    char winner[105] = "";

    int current_votes = 0;
    char current_candidate[105] = "";

    for (int i = 0; i < n; i++) {
        if (i == 0 || strcmp(votes[i], current_candidate) != 0) {
            if (current_votes > max_votes) {
                max_votes = current_votes;
                strcpy(winner, current_candidate);
            }
            strcpy(current_candidate, votes[i]);
            current_votes = 1;
        } else {
            current_votes++;
        }
    }

    if (current_votes > max_votes) {
        max_votes = current_votes;
        strcpy(winner, current_candidate);
    }

    printf("%s %d\n", winner, max_votes);

    free(votes);
    return 0;
}