#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

bool isStackFull() {
    return (top == MAX_SIZE - 1);
}

bool isStackEmpty() {
    return (top == -1);
}

void push(int item) {
    if (isStackFull()) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = item;
    printf("%d pushed to stack\n", item);
}

int pop() {
    if (isStackEmpty()) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

void displayStack() {
    if (isStackEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    int choice, item;

    while (1) {
        printf("\nStack Operations Menu\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. Display Stack\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &item);
                push(item);
                break;
            case 2:
                item = pop();
                if (item != -1)
                    printf("Popped element: %d\n", item);
                break;
            case 3:
                displayStack();
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
