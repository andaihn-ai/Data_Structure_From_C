#ifndef QUEUE_H
#define QUEUE_H
#define ARRAYSIZE 100

typedef struct 
{
    int array[ARRAYSIZE];
    int front;
    int rear;
} Queue;

int push(Queue * pq, int data);
int pop(Queue * pq);
void initQueue(Queue *pq);

#endif