#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

void push(char c) {
    if (top < MAX_SIZE - 1) {
        stack[++top] = c;
    }
}

char pop() {
    if (top >= 0) {
        return stack[top--];
    }
    return '\0';
}

char peek() {
    if (top >= 0) {
        return stack[top];
    }
    return '\0';
}

int isEmpty() {
    return top == -1;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char c;
    
    while ((c = infix[i++]) != '\0') {
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else if (isOperator(c)) {
            while (!isEmpty() && peek() != '(' && precedence(peek()) >= precedence(c)) {
                if (c == '^' && peek() == '^') {
                    break;
                }
                postfix[j++] = pop();
            }
            push(c);
        }
    }
    
    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];
    
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("%s\n", postfix);
    
    return 0;
}