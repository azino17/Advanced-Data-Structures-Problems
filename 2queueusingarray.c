#define MAX 6
#include <stdio.h>
#include <stdlib.h>

int iFront1 = 0;
int iRear1 = -1;
int iFront2 = MAX-1;
int iRear2 = MAX;

void Enqueue(int *pQueue,int iNo);
int Dequeue(int *pQueue);
int isFull();
int isEmpty();
void Display(int *pQueue);

int main(void)
{
  int Queue[MAX];
  int a,iNo,iPopped;

    while(1)
    {
        printf("Enter 1 for Enqueue\n Enter 2 for Dequeue\n Enter 3 for Display\n Enter 4 for Exit\n");
        scanf("%d",&a);
        switch (a)
        {
        case 1:
            printf("Enter element for Enqueue:\n");
            scanf("%d",&iNo);
            Enqueue(Queue,iNo);
            break;
        case 2:
            iPopped = Dequeue(Queue);
            if(iPopped!=-1)
            {
                printf("The Popped element is %d\n",iPopped);
            }
            break;
        case 3:
            Display(Queue);
            break;
        case 4:
          exit(0);
          break;
        }
    }
}

void Enqueue(int *pQueue,int iNo)
{
    if(isFull())
    {
       printf("The Both Queue are Full\n");
       return;
    }

    if(iRear1==MAX/2-1)
    {
        printf("The queue 1 is Full Now we are Enqueing in queue 2\n");
        iRear2--;
        pQueue[iRear2] = iNo;
        return;
    }

    iRear1++;
    pQueue[iRear1] = iNo;
}

int Dequeue(int *pQueue)
{
   if(isEmpty())
   {
    printf("The Both Queue is Empty we can not Dequeue:\n");
    return -1;
   }

   int iPopped;

   if(iRear1!=-1)
   {
    iPopped = pQueue[iFront1];
    if(iFront1==iRear1)
    {
        iFront1 = 0;
        iRear1 = -1;
        return iPopped;
    }
    iFront1++;
    return iPopped;
   }


   else if(iRear2!=MAX)
   {
    iPopped = pQueue[iFront2];
   if(iFront2==iRear2)
   {
     iFront2 = MAX-1;
     iRear2 = MAX;
     return iPopped;
   }
   iFront2--;
   return iPopped;
   }

}

int isFull()
{
    if(iRear2-iRear1 == 1)
    {
        return 1;
    }

    return 0;
}

int isEmpty()
{
    if(iRear1==-1 && iRear2==MAX)
    {
        return 1;
    }
    return 0;
}

void Display(int *pQueue)
{
   if(isEmpty())
   {
    printf("The Both Queue are Empty:\n");
    return;
   }

   if(iRear2!=MAX)
   {
    for(int i=iRear2;i<MAX;i++)
    {
        printf("%d\n",pQueue[i]);
    }
   }

   for(int i=iRear1;i>=0;i--)
   {
    printf("%d\n",pQueue[i]);
   }

}
