#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct QueueItem {
    struct TreeNode* node;
    int hd;
};

struct VerticalLine {
    int* values;
    int count;
    int capacity;
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

void initLine(struct VerticalLine* line) {
    line->capacity = 10;
    line->count = 0;
    line->values = (int*)malloc(line->capacity * sizeof(int));
}

void addToLine(struct VerticalLine* line, int val) {
    if (line->count == line->capacity) {
        line->capacity *= 2;
        line->values = realloc(line->values, line->capacity * sizeof(int));
    }
    line->values[line->count++] = val;
}

void verticalOrder(struct TreeNode* root, int n) {
    if (root == NULL)
        return;
    
    struct QueueItem* queue = (struct QueueItem*)malloc((n + 1) * sizeof(struct QueueItem));
    int front = 0, rear = 0;
    int minHd = 0, maxHd = 0;
    
    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;
    
    while (front < rear) {
        struct TreeNode* node = queue[front].node;
        int hd = queue[front].hd;
        front++;
        
        if (hd < minHd) minHd = hd;
        if (hd > maxHd) maxHd = hd;
        
        if (node->left) {
            queue[rear].node = node->left;
            queue[rear].hd = hd - 1;
            rear++;
        }
        if (node->right) {
            queue[rear].node = node->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }
    
    int range = maxHd - minHd + 1;
    struct VerticalLine* lines = (struct VerticalLine*)malloc(range * sizeof(struct VerticalLine));
    for (int i = 0; i < range; i++)
        initLine(&lines[i]);
    
    front = 0;
    rear = 0;
    queue[rear].node = root;
    queue[rear].hd = 0;
    rear++;
    
    while (front < rear) {
        struct TreeNode* node = queue[front].node;
        int hd = queue[front].hd;
        front++;
        
        addToLine(&lines[hd - minHd], node->val);
        
        if (node->left) {
            queue[rear].node = node->left;
            queue[rear].hd = hd - 1;
            rear++;
        }
        if (node->right) {
            queue[rear].node = node->right;
            queue[rear].hd = hd + 1;
            rear++;
        }
    }
    
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < lines[i].count; j++) {
            if (j > 0) printf(" ");
            printf("%d", lines[i].values[j]);
        }
        printf("\n");
        free(lines[i].values);
    }
    
    free(lines);
    free(queue);
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
    verticalOrder(root, n);
    
    freeTree(root);
    free(arr);
    
    return 0;
}