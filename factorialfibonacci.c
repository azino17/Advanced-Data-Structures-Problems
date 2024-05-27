// #define MAX 20
// #include <stdio.h>

// int iTop = -1;

// void Push(int*pStack,int iNo);
// int isFull(int iNo);

// int main(void)
// {
//     int iNo;
//     int i=2;
//     int Stack[MAX] = {0};

//     printf("Enter No for which you want to calculate factorial:\n");
//     scanf("%d",&iNo);

//     Push(Stack,1);

//     while (!isFull(iNo))
//     {
//       Push(Stack,Stack[iTop]*i);
//       i++;
//     }

//     printf("The Factorial is %d\n,",Stack[iTop]);

// }

// void Push(int*pStack,int iNo)
// {

//    iTop++;
//    pStack[iTop] = iNo;
// }

// int isFull(int iNo)
// {
//     if(iTop==(iNo-1))
//     {
//         return 1;
//     }
//     return 0;
// }

#define MAX 20
#include <stdio.h>

int iTop = -1;

void Push(int*pStack,int iNo);
int Pop(int*pStack);

int main(void)
{
    int n,next;
    int Stack[MAX] = {0};

    Push(Stack,0);

    printf("Enter no for whih you want Fibonacci series:\n");
    scanf("%d",&n);

    if(n>1)
    {
        Push(Stack,1);

        for(int i=2;i<n;i++)
        {
            int Second = Pop(Stack);
            int First = Pop(Stack);
            next = First+Second;
            Push(Stack,First);
            Push(Stack,Second);
            Push(Stack,next);
        }
    }

    printf("The Fibonacci is %d\n",Stack[iTop]);

}

void Push(int*pStack,int iNo)
{

   iTop++;
   pStack[iTop] = iNo;
}

int Pop(int*pStack)
{
    int iPopped;
    iPopped = pStack[iTop];
    iTop--;
    return iPopped;
}
