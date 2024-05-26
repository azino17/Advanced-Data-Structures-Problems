#include <stdio.h>
#include <stdlib.h>

// Node structure for the threaded binary tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int isThreaded; // Flag to indicate whether right pointer is a thread
};

// Function to create a new node
struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Function to insert a node into the threaded binary tree
struct Node *insert(struct Node *root, int data) {
    // If the tree is empty, create a new node and return it
    if (root == NULL) {
        return createNode(data);
    }

    // Traverse the tree to find the appropriate position to insert the new node
    struct Node *current = root;
    while (1) {
        // If data is less than the current node's data, move to the left subtree
        if (data < current->data) {
            if (current->left == NULL) {
                current->left = createNode(data);
                current->left->right = current; // Thread right pointer to the parent
                current->left->isThreaded = 1;
                break;
            } else {
                current = current->left;
            }
        }
        // If data is greater than or equal to the current node's data, move to the right subtree
        else {
            if (current->isThreaded || current->right == NULL) {
                struct Node *temp = createNode(data);
                temp->right = current->right;
                current->right = temp;
                current->isThreaded = 0; // Reset the threaded flag
                temp->isThreaded = 1;
                break;
            } else {
                current = current->right;
            }
        }
    }

    return root;
}

// Function to perform preorder traversal of the threaded binary tree
void preorderTraversal(struct Node *root) {
    struct Node *current = root;
    struct Node *prev = NULL;

    while (current != NULL) {
        printf("%d ", current->data);

        // If the current node has a left child, move to the left child
        if (current->left != NULL) {
            current = current->left;
        }
        // If the current node is threaded, move to the right node using the thread
        else if (current->isThreaded) {
            current = current->right;
        }
        // If the current node is not threaded, move to the right child
        else {
            prev = current;
            current = current->right;
            if (current != NULL && current->left != prev) {
                current = current->left;
            }
        }

        // If we have traversed back to the root node, break the loop
        if (current == root) {
            break;
        }
    }
}


// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert node\n");
    printf("2. Traverse in Preorder\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node *root = NULL;
    int choice, data;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                printf("Node inserted successfully\n");
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
