#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int search(int arr[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == value)
            return i;
    }
    return -1;
}

struct Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd)
        return NULL;
    
    struct Node* node = createNode(postorder[*postIndex]);
    (*postIndex)--;
    
    if (inStart == inEnd)
        return node;
    
    int inIndex = search(inorder, inStart, inEnd, node->data);
    
    node->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);
    
    return node;
}

void preorderTraversal(struct Node* node) {
    if (node == NULL)
        return;
    
    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void freeTree(struct Node* node) {
    if (node == NULL)
        return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    int n, i;
    
    scanf("%d", &n);
    
    int* inorder = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    for (i = 0; i < n; i++) {
        scanf("%d", &postorder[i]);
    }
    
    int postIndex = n - 1;
    
    struct Node* root = buildTree(inorder, postorder, 0, n - 1, &postIndex);
    
    preorderTraversal(root);
    printf("\n");
    
    freeTree(root);
    free(inorder);
    free(postorder);
    
    return 0;
}