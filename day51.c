#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}

struct Node* findLCA(struct Node* root, int p, int q) {
    if (root == NULL) {
        return NULL;
    }
    
    if (p < root->data && q < root->data) {
        return findLCA(root->left, p, q);
    }
    
    if (p > root->data && q > root->data) {
        return findLCA(root->right, p, q);
    }
    
    return root;
}

void freeTree(struct Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    
    struct Node* root = NULL;
    
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        root = insert(root, value);
    }
    
    int p, q;
    scanf("%d %d", &p, &q);
    
    struct Node* lca = findLCA(root, p, q);
    
    if (lca != NULL) {
        printf("%d\n", lca->data);
    }
    
    freeTree(root);
    
    return 0;
}