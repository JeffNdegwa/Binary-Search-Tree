#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for the Binary Search Tree
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to create a new tree node
TreeNode *createNode(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
TreeNode *insert(TreeNode *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

// Function to delete a node from the BST
TreeNode *deleteNode(TreeNode *root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor (smallest in the right subtree)
        TreeNode *temp = root->right;
        while (temp && temp->left != NULL)
            temp = temp->left;
        // Copy the inorder successor's content to this node
        root->data = temp->data;
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the BST
int height(TreeNode *root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
}

// Function to print the level and height of a given node
void printLevelAndHeight(TreeNode *root, int key, int level) {
    if (root == NULL) {
        printf("Node not found\n");
        return;
    }
    if (root->data == key) {
        printf("Level: %d\n", level);
        printf("Height: %d\n", height(root));
        return;
    }
    if (key < root->data)
        printLevelAndHeight(root->left, key, level + 1);
    else
        printLevelAndHeight(root->right, key, level + 1);
}

// Function to print the inorder traversal of the BST
void inorder(TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    TreeNode *root = NULL;

    // Create the BST from the array
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    // Print the inorder traversal of the BST
    printf("Inorder traversal of the BST: ");
    inorder(root);
    printf("\n");

    // Delete a node (for example, delete node with data 20)
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    printf("Inorder traversal after deleting %d: ", keyToDelete);
    inorder(root);
    printf("\n");

    // Print the height of the BST
    printf("Height of the BST: %d\n", height(root));

    // Print the level and height of a given node (for example, node with data 40)
    int keyToSearch = 40;
    printf("Node with data %d:\n", keyToSearch);
    printLevelAndHeight(root, keyToSearch, 0);

    return 0;
}
