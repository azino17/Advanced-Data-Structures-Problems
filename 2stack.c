#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 6

int topStack1 = -1;
int topStack2 = MAX_SIZE;

// Function prototypes
void push(int*, int, int);
int pop(int*, int);
int isFull(int, int);
int isEmpty(int, int);
void display(int*, int, int);

int main(void) {
    int choice, number, poppedElement;
    int stack[MAX_SIZE];

    while (1) {
        printf("Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to push: ");
                scanf("%d", &number);
                push(stack, number, MAX_SIZE);
                break;
            case 2:
                poppedElement = pop(stack, MAX_SIZE);
                if (poppedElement != -1) {
                    printf("Popped element: %d\n", poppedElement);
                }
                break;
            case 3:
                display(stack, topStack1, topStack2);
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to push an element to either stack
void push(int *stack, int element, int maxSize) {
    if (isFull(topStack1, topStack2)) {
        printf("Both stacks are full\n");
        return;
    }

    if (topStack1 == maxSize / 2 - 1) {
        printf("Stack 1 is full, pushing to Stack 2\n");
        stack[--topStack2] = element;
    } else {
        stack[++topStack1] = element;
    }
}

// Function to pop an element from either stack
int pop(int *stack, int maxSize) {
    if (isEmpty(topStack1, topStack2)) {
        printf("Both stacks are empty\n");
        return -1;
    }

    if (topStack2 == maxSize) {
        printf("Stack 2 is empty, popping from Stack 1\n");
        return stack[topStack1--];
    } else {
        return stack[topStack2++];
    }
}

// Function to check if both stacks are full
int isFull(int top1, int top2) {
    return top2 - top1 == 1;
}

// Function to check if both stacks are empty
int isEmpty(int top1, int top2) {
    return top1 == -1 && top2 == MAX_SIZE;
}

// Function to display elements of both stacks
void display(int *stack, int top1, int top2) {
    if (isEmpty(top1, top2)) {
        printf("Both stacks are empty\n");
        return;
    }

    printf("Stack elements:\n");

    if (top2 != MAX_SIZE) {
        printf("Stack 2 elements:\n");
        for (int i = top2; i < MAX_SIZE; i++) {
            printf("%d\n", stack[i]);
        }
    }

    printf("Stack 1 elements:\n");
    for (int i = top1; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}

