#include <stdio.h>
#include <stdlib.h>

// Define the structure for a Node
struct Node {
    int data;
    struct Node* lchild;
    struct Node* rchild;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// Function to calculate the height of the tree
int Height(struct Node* root) {
    int x, y;
    if (root == NULL) {
        return -1;
    }
    x = Height(root->lchild);
    y = Height(root->rchild);
    return (x > y) ? x + 1 : y + 1;
}

void insertNode(struct Node* current, struct Node* newNode) {
    if (current->lchild == NULL) {
        current->lchild = newNode;
    } else if (current->rchild == NULL) {
        current->rchild = newNode;
    } else {
        // If both children are present, insert in the left subtree
        // If the left subtree is full, then insert in the right subtree
        int leftHeight = Height(current->lchild);
        int rightHeight = Height(current->rchild);
        if (leftHeight <= rightHeight) {
            insertNode(current->lchild, newNode);
        } else {
            insertNode(current->rchild, newNode);
        }
    }
}

// Function to insert a node in the binary tree in level order
struct Node* insertLevelOrder(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    // Use a recursive helper function to find the first available spot
    struct Node* current = root;
    struct Node* newNode = createNode(data);
    insertNode(current, newNode);
    return root;
}



// Inorder traversal
void Inorder(struct Node* p) {
    if (p != NULL) {
        Inorder(p->lchild);
        printf(" %d", p->data);
        Inorder(p->rchild);
    }
}

// Inorder traversal without recursion
void InorderR(struct Node* p) {
    if (p == NULL) {
        printf("Tree is Empty");
        return;
    }
    struct Node* stack[100];
    int top = -1;
    struct Node* t = p;

    while (t != NULL || top != -1) {
        while (t != NULL) {
            stack[++top] = t;
            t = t->lchild;
        }
        if (top != -1) {
            t = stack[top--];
            printf("%d ", t->data);
            t = t->rchild;
        }
    }
}

// Preorder traversal without recursion
void PreorderR(struct Node* p) {
    if (p == NULL) {
        printf("Tree is Empty");
        return;
    }
    struct Node* stack[100];
    int top = -1;
    struct Node* t = p;

    while (t != NULL || top != -1) {
        while (t != NULL) {
            printf("%d ", t->data);
            stack[++top] = t;
            t = t->lchild;
        }
        if (top != -1) {
            t = stack[top--];
            t = t->rchild;
        }
    }
}

// Postorder traversal without recursion
void PostorderR(struct Node* p) {
    if (p == NULL) {
        printf("Tree is Empty");
        return;
    }
    struct Node* stack[100];
    int top = -1;
    struct Node* t = p;
    struct Node* a = NULL;

    while (t != NULL || top != -1) {
        while (t != NULL) {
            stack[++top] = t;
            t = t->lchild;
        }
        t = stack[top];
        if (t->rchild == NULL || t->rchild == a) {
            printf("%d ", t->data);
            top--;
            a = t;
            t = NULL;
        } else {
            t = t->rchild;
        }
    }
}

// Preorder traversal
void Preorder(struct Node* p) {
    if (p != NULL) {
        printf("%d ", p->data);
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
}

// Postorder traversal
void Postorder(struct Node* p) {
    if (p != NULL) {
        Postorder(p->lchild);
        Postorder(p->rchild);
        printf("%d ", p->data);
    }
}



// Function to count the total number of nodes in the tree
int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->lchild) + countNodes(root->rchild);
}

// Function to count the number of leaf nodes in the tree
int countLeafNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL) {
        return 1;
    }
    return countLeafNodes(root->lchild) + countLeafNodes(root->rchild);
}

// Function to display the leaf nodes of the tree
void displayLeafNodes(struct Node* root) {
    if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
            printf("%d ", root->data);
        }
        displayLeafNodes(root->lchild);
        displayLeafNodes(root->rchild);
    }
}

// Function to create the mirror image of the tree
void mirror(struct Node* root) {
    if (root == NULL) {
        return;
    }
    struct Node* temp;

    // Recursively mirror the left and right subtrees
    mirror(root->lchild);
    mirror(root->rchild);

    // Swap the left and right children
    temp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = temp;
}

// Function to display the mirror image of the tree (inorder traversal of mirrored tree)
void displayMirrorImage(struct Node* root) {
    if (root != NULL) {
        displayMirrorImage(root->rchild);
        printf("%d ", root->data);
        displayMirrorImage(root->lchild);
    }
}

// Function to display the tree in level order (iterative approach)
void levelOrderwithoutRecursion(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node* queue[100]; // Assume a maximum of 100 nodes
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->lchild != NULL) {
            queue[rear++] = current->lchild;
        }
        if (current->rchild != NULL) {
            queue[rear++] = current->rchild;
        }
    }
}

// Function to display nodes at a given level (helper for recursive approach)
void printGivenLevel(struct Node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printGivenLevel(root->lchild, level - 1);
        printGivenLevel(root->rchild, level - 1);
    }
}

// Function to display the tree in level order (recursive approach)
void levelOrderRecursive(struct Node* root) {
    int h = Height(root) + 1; // +1 because Height function returns the height as depth - 1
    for (int i = 1; i <= h; i++) {
        printGivenLevel(root, i);
    }
}

// Menu-driven program
int main() {
    struct Node* root = NULL;
    int* element;
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);
    element = (int*)malloc(size * sizeof(int));
    printf("Enter %d elements: ", size);
    for (int i = 0; i < size; ++i) {
        scanf("%d", &element[i]);
    }
    for (int i = 0; i < size; ++i) {
        root = insertLevelOrder(root, element[i]);
    }

    int n;

    do {
        printf("\nBinary Tree Operations:\n");
        printf("1. Preorder Traversal:\n");
        printf("2. Preorder without Recursion:\n");
        printf("3. Postorder Traversal:\n");
        printf("4. Postorder without Recursion:\n");
        printf("5. Inorder Traversal:\n");
        printf("6. Inorder without Recursion:\n");
        printf("7. Delete:\n"); // Not supported for now
        printf("8. Display Height:\n");
        printf("9. Count Leaf Nodes:\n");
        printf("10. Count Total Number of Nodes:\n");
        printf("11. Display Leaf Nodes:\n");
        printf("12. Display Mirror Image:\n");
        printf("13. Display Level Order with Recursion:\n");
        printf("14. Display Level Order without Recursion:\n");
        printf("15. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                printf("Preorder Traversal: ");
                Preorder(root);
                printf("\n");
                break;
            case 2:
                printf("Preorder Traversal without Recursion: ");
                PreorderR(root);
                printf("\n");
                break;
            case 3:
                printf("Postorder Traversal: ");
                Postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal without Recursion: ");
                PostorderR(root);
                printf("\n");
                break;
            case 5:
                printf("Inorder Traversal: ");
                Inorder(root);
                printf("\n");
                break;
            case 6:
                printf("Inorder Traversal without Recursion: ");
                InorderR(root);
                printf("\n");
                break;
            case 7:
                printf("Delete operation is not supported in this version of Binary Tree\n");
                break;
            case 8:
                printf("Height of the Tree: %d\n", Height(root));
                break;
            case 9:
                printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 10:
                printf("Total Number of Nodes in the Tree: %d\n", countNodes(root));
                break;
            case 11:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 12:
                printf("Mirror Image Inorder Traversal: ");
                mirror(root);
                displayMirrorImage(root);
                mirror(root);  // Restore the original tree structure
                printf("\n");
                break;
            case 13:
                printf("Level Order Traversal (Recursive): ");
                levelOrderRecursive(root);
                printf("\n");
                break;
            case 14:
                printf("Level Order Traversal without Recursion: ");
                levelOrderwithoutRecursion(root);
                printf("\n");
                break;
            case 15:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (n != 15);

    free(element);
    return 0;
}
