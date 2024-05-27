#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    struct ListNode *prev;
    int data;
    struct ListNode *next;
};

// Function prototypes
void insertLast(struct ListNode **head, int num);
void display(struct ListNode *head);
void mergeLinkedLists(struct ListNode *head1, struct ListNode *head2, struct ListNode **result);

int main(void)
{
    struct ListNode *first = NULL;
    struct ListNode *second = NULL;
    struct ListNode *merged = NULL;

    int choice, num;

    // Menu loop
    while (1)
    {
        // Displaying menu
        printf("\nMenu:\n");
        printf("1. Insert element into first linked list\n");
        printf("2. Insert element into second linked list\n");
        printf("3. Merge the two linked lists\n");
        printf("4. Display merged linked list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Performing operation based on user choice
        switch (choice)
        {
        case 1:
            printf("Enter the number to insert into the first linked list: ");
            scanf("%d", &num);
            insertLast(&first, num);
            break;
        case 2:
            printf("Enter the number to insert into the second linked list: ");
            scanf("%d", &num);
            insertLast(&second, num);
            break;
        case 3:
            mergeLinkedLists(first, second, &merged);
            printf("Lists merged successfully.\n");
            break;
        case 4:
            printf("Merged linked list: ");
            display(merged);
            break;
        case 5:
            printf("Exiting...\n");
            // Free memory before exit if necessary
            return 0;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to insert a node at the end of the list
void insertLast(struct ListNode **head, int num)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    newNode->data = num;
    newNode->next = NULL;

    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    struct ListNode *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Function to display the linked list
void display(struct ListNode *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to merge two sorted linked lists
void mergeLinkedLists(struct ListNode *head1, struct ListNode *head2, struct ListNode **result)
{
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data < head2->data)
        {
            insertLast(result, head1->data);
            head1 = head1->next;
        }
        else if (head1->data > head2->data)
        {
            insertLast(result, head2->data);
            head2 = head2->next;
        }
        else
        {
            insertLast(result, head1->data);
            insertLast(result, head2->data);
            head1 = head1->next;
            head2 = head2->next;
        }
    }

    while (head1 != NULL)
    {
        insertLast(result, head1->data);
        head1 = head1->next;
    }

    while (head2 != NULL)
    {
        insertLast(result, head2->data);
        head2 = head2->next;
    }
}

