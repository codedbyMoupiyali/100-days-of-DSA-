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

int getLength(struct Node* head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

int main() {
    int n, m, val, i;
    struct Node *head1 = NULL, *tail1 = NULL;
    struct Node *head2 = NULL, *tail2 = NULL;
    struct Node *newNode, *ptr1, *ptr2;
    int len1, len2, diff;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        newNode = createNode(val);
        if (head1 == NULL)
            head1 = tail1 = newNode;
        else {
            tail1->next = newNode;
            tail1 = newNode;
        }
    }

    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &val);
        newNode = createNode(val);
        if (head2 == NULL)
            head2 = tail2 = newNode;
        else {
            tail2->next = newNode;
            tail2 = newNode;
        }
    }

    len1 = getLength(head1);
    len2 = getLength(head2);
    ptr1 = head1;
    ptr2 = head2;

    if (len1 > len2) {
        diff = len1 - len2;
        for (i = 0; i < diff; i++)
            ptr1 = ptr1->next;
    } else {
        diff = len2 - len1;
        for (i = 0; i < diff; i++)
            ptr2 = ptr2->next;
    }

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->data == ptr2->data) {
            printf("%d\n", ptr1->data);
            return 0;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    printf("No Intersection\n");
    return 0;
}