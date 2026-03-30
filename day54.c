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

void zigzagTraversal(struct TreeNode* root, int n) {
    if (root == NULL)
        return;
    
    struct TreeNode** queue = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    int* levelValues = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    int leftToRight = 1;
    int first = 1;
    
    queue[rear++] = root;
    
    while (front < rear) {
        int levelSize = rear - front;
        int levelCount = 0;
        
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            levelValues[levelCount++] = node->val;
            
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
        
        if (leftToRight) {
            for (int i = 0; i < levelCount; i++) {
                if (!first) printf(" ");
                printf("%d", levelValues[i]);
                first = 0;
            }
        } else {
            for (int i = levelCount - 1; i >= 0; i--) {
                if (!first) printf(" ");
                printf("%d", levelValues[i]);
                first = 0;
            }
        }
        
        leftToRight = !leftToRight;
    }
    
    printf("\n");
    free(queue);
    free(levelValues);
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
    zigzagTraversal(root, n);
    
    freeTree(root);
    free(arr);
    
    return 0;
}