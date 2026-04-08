#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue *create_queue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *n = (QueueNode *)malloc(sizeof(QueueNode));
    n->tree_node = tree_node;
    n->next = NULL;
    if (q->rear) {
        q->rear->next = n;
    } else {
        q->front = n;
    }
    q->rear = n;
}

TreeNode *dequeue(Queue *q) {
    if (!q->front) {
        return NULL;
    }
    QueueNode *f = q->front;
    TreeNode *t = f->tree_node;
    q->front = f->next;
    if (!q->front) {
        q->rear = NULL;
    }
    free(f);
    return t;
}

bool is_empty(Queue *q) { return q->front == NULL; }

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode *build_tree_by_level(int *level_order, int size) {
    if (size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = root->right = NULL;
    Queue *q = create_queue();
    enqueue(q, root);
    int i = 1;
    while (i < size && !is_empty(q)) {
        TreeNode *node = dequeue(q);
        if (i < size) {
            if (level_order[i] != INT_MIN) {
                node->left = (TreeNode *)malloc(sizeof(TreeNode));
                node->left->val = level_order[i];
                node->left->left = node->left->right = NULL;
                enqueue(q, node->left);
            }
            i++;
        }
        if (i < size) {
            if (level_order[i] != INT_MIN) {
                node->right = (TreeNode *)malloc(sizeof(TreeNode));
                node->right->val = level_order[i];
                node->right->left = node->right->right = NULL;
                enqueue(q, node->right);
            }
            i++;
        }
    }
    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (!root) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    if (!root) {
        return;
    }
    TreeNode *stack[128];
    int top = 0;
    stack[top++] = root;
    while (top > 0) {
        TreeNode *n = stack[--top];
        printf("%d ", n->val);
        if (n->right) {
            stack[top++] = n->right;
        }
        if (n->left) {
            stack[top++] = n->left;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
