#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct QueueNode {
    struct TreeNode* data;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

void enqueue(struct Queue* q, struct TreeNode* node) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = node;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

struct TreeNode* dequeue(struct Queue* q) {
    if (isEmpty(q))
        return NULL;
    struct QueueNode* temp = q->front;
    struct TreeNode* node = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

struct TreeNode* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;
    
    struct TreeNode* root = createNode(arr[0]);
    struct Queue* q = createQueue();
    enqueue(q, root);
    
    int i = 1;
    while (!isEmpty(q) && i < n) {
        struct TreeNode* current = dequeue(q);
        
        if (i < n) {
            if (arr[i] != -1) {
                current->left = createNode(arr[i]);
                enqueue(q, current->left);
            }
            i++;
        }
        
        if (i < n) {
            if (arr[i] != -1) {
                current->right = createNode(arr[i]);
                enqueue(q, current->right);
            }
            i++;
        }
    }
    
    free(q);
    return root;
}

struct TreeNode* findLCA(struct TreeNode* root, int p, int q) {
    if (root == NULL)
        return NULL;
    
    if (root->val == p || root->val == q)
        return root;
    
    struct TreeNode* leftLCA = findLCA(root->left, p, q);
    struct TreeNode* rightLCA = findLCA(root->right, p, q);
    
    if (leftLCA != NULL && rightLCA != NULL)
        return root;
    
    return (leftLCA != NULL) ? leftLCA : rightLCA;
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
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int p, q;
    scanf("%d %d", &p, &q);
    
    struct TreeNode* root = buildTree(arr, n);
    struct TreeNode* lca = findLCA(root, p, q);
    
    if (lca != NULL)
        printf("%d\n", lca->val);
    else
        printf("-1\n");
    
    freeTree(root);
    free(arr);
    
    return 0;
}