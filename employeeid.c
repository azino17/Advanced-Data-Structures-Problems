#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int emp_id;
    char name[100];
    struct Employee* left;
    struct Employee* right;
} Employee;

// Function to create a new employee node
Employee* createEmployee(int emp_id, char* name) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee record in the BST
Employee* insertEmployee(Employee* root, int emp_id, char* name) {
    if (root == NULL) {
        return createEmployee(emp_id, name);
    }
    if (emp_id < root->emp_id) {
        root->left = insertEmployee(root->left, emp_id, name);
    } else if (emp_id > root->emp_id) {
        root->right = insertEmployee(root->right, emp_id, name);
    }
    return root;
}

// Function to search for an employee by emp_id
Employee* searchEmployee(Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) {
        return root;
    }
    if (emp_id < root->emp_id) {
        return searchEmployee(root->left, emp_id);
    }
    return searchEmployee(root->right, emp_id);
}

// Function to perform in-order traversal to display employees in ascending order of emp_id
void inOrderTraversal(Employee* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("Emp ID: %d, Name: %s\n", root->emp_id, root->name);
        inOrderTraversal(root->right);
    }
}

int main() {
    Employee* root = NULL;
    int choice, emp_id;
    char name[100];

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Insert Employee\n");
        printf("2. Search Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &emp_id);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                root = insertEmployee(root, emp_id, name);
                break;
            case 2:
                printf("Enter Employee ID to search: ");
                scanf("%d", &emp_id);
                Employee* emp = searchEmployee(root, emp_id);
                if (emp != NULL) {
                    printf("Employee found - Emp ID: %d, Name: %s\n", emp->emp_id, emp->name);
                } else {
                    printf("Employee with ID %d not found\n", emp_id);
                }
                break;
            case 3:
                printf("Employee records in ascending order:\n");
                inOrderTraversal(root);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
