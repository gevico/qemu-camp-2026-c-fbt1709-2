#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct TreeNode {
    char letter;
    int count;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_node(char letter) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->letter = tolower((unsigned char)letter);
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode *insert_or_update(TreeNode *root, char letter) {
    char c = (char)tolower((unsigned char)letter);
    if (!root) {
        return create_node(c);
    }
    if (c < root->letter) {
        root->left = insert_or_update(root->left, c);
    } else if (c > root->letter) {
        root->right = insert_or_update(root->right, c);
    } else {
        root->count++;
    }
    return root;
}

void inorder_traversal(TreeNode *root) {
    if (!root) {
        return;
    }
    inorder_traversal(root->left);
    printf("%c:%d\n", root->letter, root->count);
    inorder_traversal(root->right);
}

void free_tree(TreeNode *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(int argc, char *argv[]) {
    const char *file_path = "paper.txt";

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    TreeNode *root = NULL;
    int c;

    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            root = insert_or_update(root, (char)c);
        }
    }

    fclose(file);

    inorder_traversal(root);

    free_tree(root);

    return 0;
}
