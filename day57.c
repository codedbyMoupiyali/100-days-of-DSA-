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

void mirror(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirror(root->left);
    mirror(root->right);
}

void inorder(struct TreeNode* root, int* first) {
    if (root == NULL)
        return;
    
    inorder(root->left, first);
    
    if (!(*first))
        printf(" ");
    printf("%d", root->val);
    *first = 0;
    
    inorder(root->right, first);
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
    mirror(root);
    
    int first = 1;
    inorder(root, &first);
    printf("\n");
    
    freeTree(root);
    free(arr);
    
    return 0;
}