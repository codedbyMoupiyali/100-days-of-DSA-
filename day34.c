#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;

void push(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

int pop() {
    if (top == NULL) {
        return 0;
    }
    struct Node* temp = top;
    int value = temp->data;
    top = top->next;
    free(temp);
    return value;
}

int isEmpty() {
    return top == NULL;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int evaluatePostfix(char* expression) {
    char* token = strtok(expression, " ");
    
    while (token != NULL) {
        if (strlen(token) == 1 && isOperator(token[0])) {
            int b = pop();
            int a = pop();
            int result;
            
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            push(result);
        } else {
            push(atoi(token));
        }
        token = strtok(NULL, " ");
    }
    
    return pop();
}

void freeStack() {
    while (top != NULL) {
        struct Node* temp = top;
        top = top->next;
        free(temp);
    }
}

int main() {
    char expression[1000];
    
    fgets(expression, sizeof(expression), stdin);
    
    int len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    
    int result = evaluatePostfix(expression);
    
    printf("%d\n", result);
    
    freeStack();
    
    return 0;
}