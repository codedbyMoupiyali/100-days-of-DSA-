#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;
    
    struct TreeNode* root = createNode(arr[0]);
    struct TreeNode** queue = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    int i = 1;
    while (front < rear && i < n) {
        struct TreeNode* current = queue[front++];
        
        if (i < n) {
            if (arr[i] != -1) {
                current->left = createNode(arr[i]);
                queue[rear++] = current->left;
            }
            i++;
        }
        
        if (i < n) {
            if (arr[i] != -1) {
                current->right = createNode(arr[i]);
                queue[rear++] = current->right;
            }
            i++;
        }
    }
    
    free(queue);
    return root;
}

int isMirror(struct TreeNode* left, struct TreeNode* right) {
    if (left == NULL && right == NULL)
        return 1;
    
    if (left == NULL || right == NULL)
        return 0;
    
    if (left->val != right->val)
        return 0;
    
    return isMirror(left->left, right->right) && 
           isMirror(left->right, right->left);
}

int isSymmetric(struct TreeNode* root) {
    if (root == NULL)
        return 1;
    
    return isMirror(root->left, root->right);
}

void freeTree(struct TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    struct TreeNode* root = buildTree(arr, n);
    
    if (isSymmetric(root))
        printf("YES\n");
    else
        printf("NO\n");
    
    freeTree(root);
    free(arr);
    
    return 0;
}