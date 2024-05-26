#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char student_name[100];
    int student_roll_no;
    int total_marks;
} Student;

// Swap function to swap two Student elements
void swap(Student *a, Student *b, int *swap_count) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    (*swap_count)++;
}

// Function to heapify a subtree rooted with node i which is an index in array[]
void heapify(Student array[], int n, int i, int *swap_count) {
    int largest = i;   // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && array[left].student_roll_no > array[largest].student_roll_no)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && array[right].student_roll_no > array[largest].student_roll_no)
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&array[i], &array[largest], swap_count);
        // Recursively heapify the affected sub-tree
        heapify(array, n, largest, swap_count);
    }
}

// Function to build a Max-Heap from the array
void buildHeap(Student array[], int n, int *swap_count) {
    // Index of last non-leaf node
    int start_idx = (n / 2) - 1;

    // Perform reverse level order traversal from last non-leaf node and heapify each node
    for (int i = start_idx; i >= 0; i--) {
        heapify(array, n, i, swap_count);
    }
}

// Main function to perform Heap Sort
void heapSort(Student array[], int n, int *swap_count) {
    // Build heap (rearrange array)
    buildHeap(array, n, swap_count);

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&array[0], &array[i], swap_count);

        // Call max heapify on the reduced heap
        heapify(array, i, 0, swap_count);
    }
}

// Function to print the array of Students
void printArray(Student array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Roll No: %d, Total Marks: %d\n", array[i].student_name, array[i].student_roll_no, array[i].total_marks);
    }
}

// Function to add a student to the array
void addStudent(Student array[], int *n) {
    if (*n >= 100) {
        printf("Array is full!\n");
        return;
    }
    printf("Enter Student Name: ");
    scanf("%s", array[*n].student_name);
    printf("Enter Student Roll No: ");
    scanf("%d", &array[*n].student_roll_no);
    printf("Enter Total Marks: ");
    scanf("%d", &array[*n].total_marks);
    (*n)++;
}

int main() {
    Student students[100];
    int n = 0;
    int swap_count = 0;
    int choice;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Sort Students by Roll No (Heap Sort)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &n);
                break;
            case 2:
                printf("\nStudents List:\n");
                printArray(students, n);
                break;
            case 3:
                swap_count = 0;
                heapSort(students, n, &swap_count);
                printf("\nStudents sorted by Roll No:\n");
                printArray(students, n);
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
