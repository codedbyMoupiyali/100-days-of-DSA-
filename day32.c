#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int val) {
    if (top == MAX - 1)
        return;
    top++;
    stack[top] = val;
}

void pop() {
    if (top == -1)
        return;
    top--;
}

void display() {
    if (top == -1) {
        printf("Stack is Empty\n");
        return;
    }
    for (int i = top; i >= 0; i--) {
        if (i == top)
            printf("%d", stack[i]);
        else
            printf(" %d", stack[i]);
    }
    printf("\n");
}

int main() {
    int n, m, val;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        push(val);
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        pop();
    }

    display();

    return 0;
}