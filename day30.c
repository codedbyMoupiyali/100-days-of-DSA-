#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(struct Node** head, struct Node** tail, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void displayPolynomial(struct Node* head) {
    struct Node* temp = head;
    int isFirst = 1;

    while (temp != NULL) {
        if (!isFirst)
            printf(" + ");

        if (temp->exp == 0)
            printf("%d", temp->coeff);
        else if (temp->exp == 1)
            printf("%dx", temp->coeff);
        else
            printf("%dx^%d", temp->coeff, temp->exp);

        isFirst = 0;
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    int n, coeff, exp, i;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        insertEnd(&head, &tail, coeff, exp);
    }

    displayPolynomial(head);

    return 0;
}