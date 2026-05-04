#include <stdio.h>
#include <stdlib.h>

struct Node {
    float data;
    struct Node* next;
};

void insertionSort(struct Node** head) {
    if (!(*head) || !((*head)->next)) return;
    struct Node* sorted = NULL;
    struct Node* curr = *head;
    while (curr) {
        struct Node* next = curr->next;
        if (!sorted || sorted->data >= curr->data) {
            curr->next = sorted;
            sorted = curr;
        } else {
            struct Node* temp = sorted;
            while (temp->next && temp->next->data < curr->data) temp = temp->next;
            curr->next = temp->next;
            temp->next = curr;
        }
        curr = next;
    }
    *head = sorted;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    float arr[n];
    struct Node* buckets[n];
    for (int i = 0; i < n; i++) {
        scanf("%f", &arr[i]);
        buckets[i] = NULL;
    }
    for (int i = 0; i < n; i++) {
        int idx = n * arr[i];
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }
    for (int i = 0; i < n; i++) insertionSort(&buckets[i]);
    int k = 0;
    for (int i = 0; i < n; i++) {
        struct Node* curr = buckets[i];
        while (curr) {
            arr[k++] = curr->data;
            struct Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    for (int i = 0; i < n; i++) printf("%.2f ", arr[i]);
    printf("\n");
    return 0;
}