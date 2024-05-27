#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *pLeft;
    int lBit;
    int iData;
    int rBit;
    struct node *pRight;
};

void InOrder(struct node *pHead);
void PreOrder(struct node *pHead);
void Insert_TBT(struct node **ppHead, int iNo);

int main() {
    struct node *pHead = NULL;

    pHead = (struct node *)malloc(sizeof(struct node));
    if (pHead == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }

    pHead->lBit = 0;
    pHead->rBit = 1;
    pHead->pLeft = pHead->pRight = pHead;

    int choice, value;

    do {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. InOrder Traversal\n");
        printf("3. PreOrder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                Insert_TBT(&pHead, value);
                break;
            case 2:
                printf("InOrder Traversal:\n");
                InOrder(pHead);
                printf("\n");
                break;
            case 3:
                printf("PreOrder Traversal:\n");
                PreOrder(pHead);
                printf("\n");
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

void Insert_TBT(struct node **ppHead, int iNo) {
    struct node *pNewnode = NULL;
    struct node *pTemp = NULL;
    int iCount = 0;

    pNewnode = (struct node *)malloc(sizeof(struct node));
    if (pNewnode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    pNewnode->lBit = pNewnode->rBit = 0;
    pNewnode->iData = iNo;

    if ((*ppHead)->lBit == 0) {
        pNewnode->pLeft = pNewnode->pRight = *ppHead;
        (*ppHead)->pLeft = pNewnode;
        (*ppHead)->lBit = 1;
        return;
    }
    pTemp = (*ppHead)->pLeft;

    while (1) {
        if (pTemp->iData > iNo && pTemp->lBit == 1) {
            pTemp = pTemp->pLeft;
            iCount = 1;
        } else if (pTemp->iData < iNo && pTemp->rBit == 1) {
            pTemp = pTemp->pRight;
            iCount = 2;
        } else {
            break;
        }
    }

    if (iCount == 1) {
        pTemp->lBit = 1;
        pNewnode->pLeft = pTemp->pLeft;
        pTemp->pLeft = pNewnode;
        pNewnode->pRight = pTemp;
    } else {
        pTemp->rBit = 1;
        pNewnode->pRight = pTemp->pRight;
        pTemp->pRight = pNewnode;
        pNewnode->pLeft = pTemp;
    }
}

void InOrder(struct node *pHead) {
    struct node *pTemp = pHead->pLeft;

    if (pTemp == pHead) {
        printf("Tree is empty\n");
        return;
    }

    while (pTemp->lBit == 1) {
        pTemp = pTemp->pLeft;
    }

    while (pTemp != pHead) {
        printf("%d\t", pTemp->iData);
        if (pTemp->rBit == 0) {
            pTemp = pTemp->pRight;
        } else {
            pTemp = pTemp->pRight;
            while (pTemp->lBit == 1) {
                pTemp = pTemp->pLeft;
            }
        }
    }
}

void PreOrder(struct node *pHead) {
    struct node *pTemp = pHead->pLeft;

    if (pTemp == pHead) {
        printf("Tree is empty\n");
        return;
    }

    while (pTemp != pHead) {
        printf("%d\t", pTemp->iData);
        if (pTemp->lBit == 1) {
            pTemp = pTemp->pLeft;
        } else {
            while (pTemp->rBit == 0 && pTemp->pRight != pHead) {
                pTemp = pTemp->pRight;
            }
            pTemp = pTemp->pRight;
        }
    }
}
