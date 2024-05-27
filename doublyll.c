#include  <stdio.h>
#include <stdlib.h>

struct node
{
    struct node*pPrev;
    int iData;
    struct node*pNext;
};

void InsertFirst(struct node**ppHead,int iNo);
void InsertLast(struct node**ppHead,int iNo);
int CountNodes(struct node*pHead);
void InsertAtPosition(struct node**ppHead,int iNo,int iPos);
int DeleteFirst(struct node**ppHead);
int DeleteLast(struct node**ppHead);
int DeleteAtPosition(struct node**ppHead,int iPos);
void Display(struct node*pHead);

int main(void)
{
   struct node*pFirst = NULL;

   InsertFirst(&pFirst,10);
   InsertFirst(&pFirst,20);
   InsertFirst(&pFirst,30);
   InsertAtPosition(&pFirst,40,2);
   Display(pFirst);
   InsertLast(&pFirst,50);
   InsertLast(&pFirst,60);
   Display(pFirst);
   DeleteFirst(&pFirst);
   InsertAtPosition(&pFirst,70,3);
   Display(pFirst);
   DeleteLast(&pFirst);
   DeleteAtPosition(&pFirst,2);
   Display(pFirst);
}

void InsertFirst(struct node**ppHead,int iNo)
{
    struct node*pNewnode = NULL;

    pNewnode = (struct node*)malloc(sizeof(struct node));

    if(NULL==pNewnode)
    {
        printf("Memory Allocation Failed");
        return;
    }

    pNewnode->iData = iNo;
    pNewnode->pNext = NULL;
    pNewnode->pPrev = NULL;

   if(*ppHead==NULL)
   {
      *ppHead = pNewnode;
      return;
   }

   pNewnode->pNext = *ppHead;
   (*ppHead)->pPrev = pNewnode;
   *ppHead = pNewnode;
}

void InsertLast(struct node**ppHead,int iNo)
{
    struct node*pNewnode = NULL;
    struct node*pTemp = NULL;

    pNewnode = (struct node*)malloc(sizeof(struct node));

    if(NULL==pNewnode)
    {
        printf("Memory Allocation Failed");
        return;
    }

    pNewnode->pNext = NULL;
    pNewnode->iData = iNo;

    if(NULL==*ppHead)
    {
      *ppHead = pNewnode;
      pNewnode->pPrev = NULL;
      return;
    }

    pTemp = *ppHead;

    while (pTemp->pNext!=NULL)
    {
        pTemp = pTemp->pNext;
    }

    pTemp->pNext = pNewnode;
    pNewnode->pPrev = pTemp;
}

int CountNodes(struct node*pHead)
{
    int icount=0;
    while(pHead!=NULL)
    {
        icount++;
        pHead = pHead->pNext;
    }
    return icount;
}

void InsertAtPosition(struct node**ppHead,int iNo,int iPos)
{
     struct node*pNewNode = NULL;
     struct node*pTemp = NULL;
     int iCount = CountNodes(*ppHead);

  if(iPos<=0||iPos>(iCount+1))
  {
    printf("Invalid Position");
    return;
  }

  if(iPos==1)
  {
    InsertFirst(ppHead,iNo);
    return;
  }

  if(iPos==iCount+1)
  {
    InsertLast(ppHead,iNo);
    return;
  }

  pNewNode = (struct node*)malloc(sizeof(struct node));
  pNewNode->iData = iNo;
  if(NULL==pNewNode)
  {
    printf("Memory Allocation Failed");
    return;
  }

   pTemp = *ppHead;
   iCount = 1;

  while(iCount<iPos-1)
  {
    iCount++;
    pTemp = pTemp->pNext;
  }
  pNewNode->pNext = pTemp->pNext;
  pTemp->pNext->pPrev = pNewNode;
  pTemp->pNext = pNewNode;
  pNewNode->pPrev = pTemp;
}

int DeleteFirst(struct node**ppHead)
{
    struct node*pTemp = NULL;
    int iDelData;
    pTemp = *ppHead;

    iDelData = (*ppHead)->iData;
    (*ppHead) = pTemp->pNext;
if(pTemp->pNext!=NULL)
{
    pTemp->pNext->pPrev = NULL;
}
    pTemp->pNext = NULL;
    pTemp->pPrev =NULL;
    free(pTemp);
    return iDelData;

}

int DeleteLast(struct node**ppHead)
{
    int iDelData;
    struct node*pTemp = NULL;

    if(*ppHead==NULL)
    {
        return -1;
    }

    pTemp = *ppHead;
    while (pTemp->pNext!=NULL)
    {
        pTemp = pTemp->pNext;
    }

    iDelData = pTemp->iData;
    if(pTemp->pPrev!=NULL)   //If more than one node
    {
        pTemp->pPrev->pNext = NULL;
        pTemp->pPrev = NULL;
    }
    else
    {
        *ppHead = NULL;
    }

    free(pTemp);
    pTemp = NULL;
    return iDelData;

}

int DeleteAtPosition(struct node**ppHead,int iPos)
{
   int iCount = CountNodes(*ppHead);
   struct node*pTemp = NULL;


   if(iPos<=0 || iPos>iCount)
   {
    printf("Invalid Position");
    return -1;
   }

   if(iPos==1)
   {
     return DeleteFirst(ppHead);
   }

   if(iPos==iCount)
   {
     return DeleteLast(ppHead);
   }

   iCount = 1;
   pTemp = *ppHead;

   while (iCount<iPos)
   {
     iCount++;
     pTemp = pTemp->pNext;
   }

   iCount = pTemp->iData;
   pTemp->pPrev->pNext = pTemp->pNext;
   pTemp->pNext->pPrev = pTemp->pPrev;
   pTemp->pNext=pTemp->pPrev= NULL;
   free(pTemp);
   pTemp = NULL;
   return iCount;

}

void Display(struct node*pHead)
{
    if(NULL==pHead)
    {
        printf("List is Empty");
        return;
    }

    while(pHead!=NULL)
    {
        printf("|%d|->",pHead->iData);
        pHead = pHead->pNext;
    }
    printf("\n");
}
