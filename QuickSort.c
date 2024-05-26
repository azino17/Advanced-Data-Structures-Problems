#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char employee_name[100];
    int emp_no;
    float emp_salary;
} Employee;

// Function to swap two Employee elements
void swap(Employee *a, Employee *b, int *swap_count) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
    (*swap_count)++;
}

// Partition function for Quick Sort
int partition(Employee array[], int low, int high, int *swap_count) {
    int pivot = array[high].emp_no; // Pivot element
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (array[j].emp_no <= pivot) {
            i++; // Increment index of smaller element
            swap(&array[i], &array[j], swap_count);
        }
    }
    swap(&array[i + 1], &array[high], swap_count);
    return (i + 1);
}

// Quick Sort function
void quickSort(Employee array[], int low, int high, int *swap_count) {
    if (low < high) {
        int pi = partition(array, low, high, swap_count); // Partitioning index

        quickSort(array, low, pi - 1, swap_count); // Sort the elements before partition
        quickSort(array, pi + 1, high, swap_count); // Sort the elements after partition
    }
}

// Function to print the array of Employees
void printArray(Employee array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Emp No: %d, Salary: %.2f\n", array[i].employee_name, array[i].emp_no, array[i].emp_salary);
    }
}

// Function to add an employee to the array
void addEmployee(Employee array[], int *n) {
    if (*n >= 100) {
        printf("Array is full!\n");
        return;
    }
    printf("Enter Employee Name: ");
    scanf("%s", array[*n].employee_name);
    printf("Enter Employee Number: ");
    scanf("%d", &array[*n].emp_no);
    printf("Enter Employee Salary: ");
    scanf("%f", &array[*n].emp_salary);
    (*n)++;
}

int main() {
    Employee employees[100];
    int n = 0;
    int swap_count = 0;
    int choice;

    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Sort Employees by Employee Number (Quick Sort)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &n);
                break;
            case 2:
                printf("\nEmployees List:\n");
                printArray(employees, n);
                break;
            case 3:
                swap_count = 0;
                quickSort(employees, 0, n - 1, &swap_count);
                printf("\nEmployees sorted by Employee Number:\n");
                printArray(employees, n);
                printf("\nNumber of swaps performed: %d\n", swap_count);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
