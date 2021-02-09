#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

void initQueue(Queue *pq, int size, int eleSize)
{
    pq -> pArr = malloc(eleSize* size);
    
    assert(pq->pArr);

    pq -> eleSize = eleSize;
    pq ->size = size;
    pq -> front = 0;
    pq -> rear = 0;
}  
void cleanUp(Queue * pq)
{
    free(pq -> pArr);
}
void push(Queue * pq, const void *pData)
{
    assert(pq->rear != pq->size);
    /* memcpy(&pq->pArr[pq->rear],pData,pq->eleSize); */
    memcpy( (unsigned char*)pq->pArr + pq->eleSize * pq->rear, pData, pq->eleSize);
    ++pq->rear;

}
void pop(Queue * pq, void *pData)
{
    assert(pq->front != pq->rear);
    
    int tmp = pq-> front;
    ++pq->front;
    
    memcpy( pData, (unsigned char*)pq->pArr + pq->eleSize * tmp, pq->eleSize);
}
