#ifndef QUEUE_H
#define QUEUE_H

typedef struct 
{
    void *pArr;
    int eleSize;
    int size;
    int front;
    int rear;
} Queue;

void initQueue(Queue *pq, int size, int eleSize);
void cleanUp(Queue * pq);

void push(Queue * pq, const void *pData);
void pop(Queue * pq, void *pData);

#endif