#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue *pq)
{
    pq -> front = 0;
    pq -> rear = 0;
}  

int push(Queue * pq, int data)
{
    if(pq->rear == ARRAYSIZE)
    {
        fprintf(stderr, "Queue is full\n");
        exit(1);
    }
    pq->array[pq->rear] = data;
    ++pq->rear;

}
int pop(Queue * pq)
{
    if(pq->front == pq->rear){
        fprintf(stderr,"Queue is empty\n");
        exit(2);
    }
    int tmp = pq-> front;
    ++pq->front;
    return pq->array[tmp];
}
