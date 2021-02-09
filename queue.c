#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
int queue[10];
int front;
int rear;

int push(int data)
{
    queue[rear] = data;
    ++rear;

}
int pop(void)
{
    int tmp = front;
    ++front;
    return queue[tmp];
}

