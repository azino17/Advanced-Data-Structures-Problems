#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Hash Table Structure
typedef struct HashTable {
    Node* table[TABLE_SIZE];
    int collisions;
} HashTable;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize hash table
void initializeTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    ht->collisions = 0;
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Insert into hash table with replacement
void insert(HashTable* ht, int data) {
    int index = hashFunction(data);

    if (ht->table[index] == NULL) {
        ht->table[index] = createNode(data);
    } else {
        ht->collisions++;
        Node* newNode = createNode(data);
        Node* temp = ht->table[index];

        // If the current node at index should be replaced
        if (hashFunction(temp->data) == index) {
            // Insert new node and move the old node to the new position
            newNode->next = temp->next;
            ht->table[index] = newNode;
            int new_index = (index + 1) % TABLE_SIZE;

            while (ht->table[new_index] != NULL) {
                ht->collisions++;
                new_index = (new_index + 1) % TABLE_SIZE;
            }
            ht->table[new_index] = temp;
        } else {
            // Append to the linked list at that index
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
}

// Search in hash table
Node* search(HashTable* ht, int data) {
    int index = hashFunction(data);
    Node* temp = ht->table[index];
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Display hash table
void displayTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node* temp = ht->table[i];
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("Total Collisions: %d\n", ht->collisions);
}

int main() {
    HashTable ht;
    initializeTable(&ht);

    int choice, data;
    do {
        printf("\nHash Table Menu\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(&ht, data);
                break;
            case 2:
                printf("Enter data to search: ");
                scanf("%d", &data);
                Node* result = search(&ht, data);
                if (result != NULL) {
                    printf("Data %d found in hash table.\n", data);
                } else {
                    printf("Data %d not found in hash table.\n", data);
                }
                break;
            case 3:
                displayTable(&ht);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
