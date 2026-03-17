#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct Deque {
    Node* front;
    Node* rear;
    int size;
} Deque;

Deque* createDeque() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
    return deque;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(Deque* deque) {
    return deque->size == 0;
}

int getSize(Deque* deque) {
    return deque->size;
}

void pushFront(Deque* deque, int value) {
    Node* newNode = createNode(value);
    
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    deque->size++;
}

void pushBack(Deque* deque, int value) {
    Node* newNode = createNode(value);
    
    if (isEmpty(deque)) {
        deque->front = newNode;
        deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    deque->size++;
}

int popFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    
    Node* temp = deque->front;
    int value = temp->data;
    
    if (deque->front == deque->rear) {
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }
    
    free(temp);
    deque->size--;
    return value;
}

int popBack(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    
    Node* temp = deque->rear;
    int value = temp->data;
    
    if (deque->front == deque->rear) {
        deque->front = NULL;
        deque->rear = NULL;
    } else {
        deque->rear = deque->rear->prev;
        deque->rear->next = NULL;
    }
    
    free(temp);
    deque->size--;
    return value;
}

int getFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->front->data;
}

int getBack(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    return deque->rear->data;
}

void clear(Deque* deque) {
    while (!isEmpty(deque)) {
        popFront(deque);
    }
}

void eraseAt(Deque* deque, int index) {
    if (index < 0 || index >= deque->size) {
        printf("Invalid index\n");
        return;
    }
    
    if (index == 0) {
        popFront(deque);
        return;
    }
    
    if (index == deque->size - 1) {
        popBack(deque);
        return;
    }
    
    Node* current = deque->front;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    deque->size--;
}

void swapDeques(Deque* deque1, Deque* deque2) {
    Node* tempFront = deque1->front;
    Node* tempRear = deque1->rear;
    int tempSize = deque1->size;
    
    deque1->front = deque2->front;
    deque1->rear = deque2->rear;
    deque1->size = deque2->size;
    
    deque2->front = tempFront;
    deque2->rear = tempRear;
    deque2->size = tempSize;
}

void reverse(Deque* deque) {
    if (isEmpty(deque) || deque->size == 1) {
        return;
    }
    
    Node* current = deque->front;
    Node* temp = NULL;
    
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    temp = deque->front;
    deque->front = deque->rear;
    deque->rear = temp;
}

void merge(Deque* deque, Node* left, Node* right, Node** result) {
    if (left == NULL) {
        *result = right;
        return;
    }
    if (right == NULL) {
        *result = left;
        return;
    }
    
    if (left->data <= right->data) {
        *result = left;
        merge(deque, left->next, right, &((*result)->next));
    } else {
        *result = right;
        merge(deque, left, right->next, &((*result)->next));
    }
}

void split(Node* source, Node** front, Node** back) {
    Node* slow = source;
    Node* fast = source->next;
    
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSort(Node** headRef) {
    Node* head = *headRef;
    
    if (head == NULL || head->next == NULL) {
        return;
    }
    
    Node* front;
    Node* back;
    
    split(head, &front, &back);
    
    mergeSort(&front);
    mergeSort(&back);
    
    merge(NULL, front, back, headRef);
}

void sortDeque(Deque* deque) {
    if (isEmpty(deque) || deque->size == 1) {
        return;
    }
    
    Node* current = deque->front;
    while (current != NULL) {
        current->prev = NULL;
        current = current->next;
    }
    
    mergeSort(&deque->front);
    
    current = deque->front;
    current->prev = NULL;
    while (current->next != NULL) {
        current->next->prev = current;
        current = current->next;
    }
    deque->rear = current;
}

void resize(Deque* deque, int newSize, int defaultValue) {
    while (deque->size > newSize) {
        popBack(deque);
    }
    while (deque->size < newSize) {
        pushBack(deque, defaultValue);
    }
}

void assign(Deque* deque, int* values, int count) {
    clear(deque);
    for (int i = 0; i < count; i++) {
        pushBack(deque, values[i]);
    }
}

void display(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    
    Node* current = deque->front;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}

void displayReverse(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    
    Node* current = deque->rear;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->prev != NULL) {
            printf(" ");
        }
        current = current->prev;
    }
    printf("\n");
}

void freeDeque(Deque* deque) {
    clear(deque);
    free(deque);
}

int main() {
    int n;
    scanf("%d", &n);
    
    Deque* deque = createDeque();
    
    for (int i = 0; i < n; i++) {
        char operation[20];
        scanf("%s", operation);
        
        if (strcmp(operation, "push_front") == 0) {
            int value;
            scanf("%d", &value);
            pushFront(deque, value);
        } else if (strcmp(operation, "push_back") == 0) {
            int value;
            scanf("%d", &value);
            pushBack(deque, value);
        } else if (strcmp(operation, "pop_front") == 0) {
            int result = popFront(deque);
            if (result != -1) {
                printf("%d\n", result);
            }
        } else if (strcmp(operation, "pop_back") == 0) {
            int result = popBack(deque);
            if (result != -1) {
                printf("%d\n", result);
            }
        } else if (strcmp(operation, "front") == 0) {
            int result = getFront(deque);
            if (result != -1) {
                printf("%d\n", result);
            }
        } else if (strcmp(operation, "back") == 0) {
            int result = getBack(deque);
            if (result != -1) {
                printf("%d\n", result);
            }
        } else if (strcmp(operation, "empty") == 0) {
            printf("%s\n", isEmpty(deque) ? "true" : "false");
        } else if (strcmp(operation, "size") == 0) {
            printf("%d\n", getSize(deque));
        } else if (strcmp(operation, "clear") == 0) {
            clear(deque);
        } else if (strcmp(operation, "reverse") == 0) {
            reverse(deque);
        } else if (strcmp(operation, "sort") == 0) {
            sortDeque(deque);
        } else if (strcmp(operation, "display") == 0) {
            display(deque);
        } else if (strcmp(operation, "erase") == 0) {
            int index;
            scanf("%d", &index);
            eraseAt(deque, index);
        } else if (strcmp(operation, "resize") == 0) {
            int newSize, defaultVal;
            scanf("%d %d", &newSize, &defaultVal);
            resize(deque, newSize, defaultVal);
        }
    }
    
    freeDeque(deque);
    
    return 0;
}