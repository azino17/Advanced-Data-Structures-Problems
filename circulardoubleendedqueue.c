#define MAX_SIZE 5
#include <stdio.h>

void enqueueRear(int*, int);
int dequeueFront(int*);
void displayQueue(int*);
int isQueueFull(void);
int isQueueEmpty(void);
void enqueueFront(int*, int);
int dequeueRear(int*);

int rearIndex = -1;
int frontIndex = 0;

int main(void)
{
    int queue[MAX_SIZE] = {0};

    enqueueRear(queue, 10);
    enqueueRear(queue, 20);
    enqueueFront(queue, 30);
    enqueueFront(queue, 40);
    displayQueue(queue);

    int deletedData = dequeueRear(queue);

    if(deletedData != -1)
    {
        printf("The deleted data is %d\n", deletedData);
    }
    displayQueue(queue);

    return 0;
}

void enqueueFront(int* queue, int data)
{
    if(isQueueFull())
    {
        printf("The Queue is Full:\n");
        return;
    }

    if(isQueueEmpty())
    {
        rearIndex = frontIndex = MAX_SIZE - 1;
        queue[frontIndex] = data;
        return;
    }

    if(frontIndex == 0)
    {
        frontIndex = MAX_SIZE - 1;
        queue[frontIndex] = data;
        return;
    }

    frontIndex--;
    queue[frontIndex] = data;
}

void enqueueRear(int* queue, int data)
{
    if(isQueueFull())
    {
        printf("The Queue is Full:\n");
        return;
    }

    if(rearIndex == MAX_SIZE - 1)
    {
        rearIndex = 0;
        queue[rearIndex] = data;
        return;
    }

    rearIndex++;
    queue[rearIndex] = data;
}

int dequeueFront(int* queue)
{
    if(isQueueEmpty())
    {
        printf("The Queue is Empty:\n");
        return -1;
    }

    int deletedData = queue[frontIndex];

    if(frontIndex == rearIndex)
    {
        frontIndex = 0;
        rearIndex = -1;
        return deletedData;
    }

    if(frontIndex == MAX_SIZE - 1)
    {
        frontIndex = 0;
        return deletedData;
    }

    frontIndex++;
    return deletedData;
}

int dequeueRear(int* queue)
{
    if(isQueueEmpty())
    {
        printf("The Queue is Empty:\n");
        return -1;
    }

    int deletedData = queue[rearIndex];

    if(frontIndex == rearIndex)
    {
        rearIndex = -1;
        frontIndex = 0;
        return deletedData;
    }

    if(rearIndex == 0)
    {
        rearIndex = MAX_SIZE - 1;
        return deletedData;
    }

    rearIndex--;
    return deletedData;
}

int isQueueFull(void)
{
    if((rearIndex == MAX_SIZE - 1 && frontIndex == 0) || (rearIndex == frontIndex - 1 && rearIndex != -1))
    {
        return 1;
    }
    return 0;
}

int isQueueEmpty(void)
{
    if(rearIndex == -1)
    {
        return 1;
    }
    return 0;
}

void displayQueue(int* queue)
{
    if(isQueueEmpty())
    {
        printf("The Queue is Empty:\n");
        return;
    }

    if(rearIndex < frontIndex)
    {
        for(int i = frontIndex; i <= MAX_SIZE - 1; i++)
        {
            printf("%d\n", queue[i]);
        }
        for(int i = 0; i <= rearIndex; i++)
        {
            printf("%d\n", queue[i]);
        }
    }
    else
    {
        for(int i = frontIndex; i <= rearIndex; i++)
        {
            printf("%d\n", queue[i]);
        }
    }
}

