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

struct Node* buildTree(int preorder[], int inorder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd)
        return NULL;
    
    struct Node* node = createNode(preorder[*preIndex]);
    (*preIndex)++;
    
    if (inStart == inEnd)
        return node;
    
    int inIndex = search(inorder, inStart, inEnd, node->data);
    
    node->left = buildTree(preorder, inorder, inStart, inIndex - 1, preIndex);
    node->right = buildTree(preorder, inorder, inIndex + 1, inEnd, preIndex);
    
    return node;
}

void postorderTraversal(struct Node* node) {
    if (node == NULL)
        return;
    
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->data);
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
    int preIndex = 0;
    
    scanf("%d", &n);
    
    int* preorder = (int*)malloc(n * sizeof(int));
    int* inorder = (int*)malloc(n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }
    
    for (i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }
    
    struct Node* root = buildTree(preorder, inorder, 0, n - 1, &preIndex);
    
    postorderTraversal(root);
    printf("\n");
    
    freeTree(root);
    free(preorder);
    free(inorder);
    
    return 0;
}