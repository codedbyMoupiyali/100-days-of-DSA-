#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int val) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = val;
}

void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack[top]);
    top--;
}

void display() {
    if (top == -1) {
        printf("Stack is Empty\n");
        return;
    }
    int i;
    for (i = top; i >= 0; i--) {
        if (i == top)
            printf("%d", stack[i]);
        else
            printf(" %d", stack[i]);
    }
    printf("\n");
}

int main() {
    int n, op, val, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &op);

        if (op == 1) {
            scanf("%d", &val);
            push(val);
        } else if (op == 2) {
            pop();
        } else if (op == 3) {
            display();
        }
    }

    return 0;
}