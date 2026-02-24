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

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* dummy = createNode(0);
    struct Node* tail = dummy;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }
    
    struct Node* mergedHead = dummy->next;
    free(dummy);
    return mergedHead;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n, m, val;
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertEnd(&list1, val);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &val);
        insertEnd(&list2, val);
    }
    
    struct Node* mergedList = mergeSortedLists(list1, list2);
    
    printList(mergedList);
    
    freeList(mergedList);
    
    return 0;
}