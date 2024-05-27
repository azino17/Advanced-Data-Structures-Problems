#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

// Function prototypes
void insertLast(struct Node **head, int num);
void display(struct Node *head);
void physicalReverse(struct Node **head);
void clearList(struct Node **head);

int main(void)
{
    struct Node *first = NULL;
    int choice, num;

    // Menu loop
    while (1)
    {
        // Displaying menu
        printf("\nMenu:\n");
        printf("1. Insert at the end\n");
        printf("2. Display list\n");
        printf("3. Reverse list\n");
        printf("4. Clear list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Performing operation based on user choice
        switch (choice)
        {
            case 1:
                printf("Enter the number to insert: ");
                scanf("%d", &num);
                insertLast(&first, num);
                break;
            case 2:
                printf("List: ");
                display(first);
                break;
            case 3:
                printf("Reversing the list...\n");
                physicalReverse(&first);
                printf("List reversed.\n");
                break;
            case 4:
                printf("Clearing the list...\n");
                clearList(&first);
                printf("List cleared.\n");
                break;
            case 5:
                printf("Exiting...\n");
                clearList(&first); // Clear the list before exiting
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to insert a node at the end of the list
void insertLast(struct Node **head, int num)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    newNode->data = num;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Function to display the list
void display(struct Node *head)
{
    if (head == NULL)
    {
        printf("List is Empty\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to reverse the list
void physicalReverse(struct Node **head)
{
    struct Node *prevNode = NULL;
    struct Node *currentNode = *head;
    struct Node *nextNode = NULL;

    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }

    *head = prevNode;
}

// Function to clear the list
void clearList(struct Node **head)
{
    struct Node *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

