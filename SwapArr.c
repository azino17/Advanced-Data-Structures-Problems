#include <stdio.h>
#include <stdlib.h>

// Function to find the swapped elements in the array
void findSwappedElements(int arr[], int n, int *pos1, int *pos2) {
    *pos1 = -1;
    *pos2 = -1;

    // Iterate through the array to find the two positions
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (*pos1 == -1) {
                *pos1 = i;
            } else {
                *pos2 = i + 1;
                break;
            }
        }
    }

    // If the second misplaced element hasn't been found
    if (*pos2 == -1) {
        *pos2 = *pos1 + 1;
    }
}

int main() {
    int n;
    int pos1, pos2;

    // Get the size of the array from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Get the elements of the array from the user
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Find the swapped elements
    findSwappedElements(arr, n, &pos1, &pos2);

    if (pos1 != -1 && pos2 != -1) {
        printf("Swapped elements are: %d and %d\n", arr[pos1], arr[pos2]);
        printf("Their positions are: %d and %d\n", pos1, pos2);
    } else {
        printf("No swapped elements found\n");
    }

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}
