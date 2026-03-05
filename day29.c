#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void traverse(struct Node* head) {
    if (head == NULL)
        return;

    struct Node* temp = head;

    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("\n");
}

int main() {
    int n, val, i;
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* newNode;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        newNode = createNode(val);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }

    traverse(head);

    return 0;
}