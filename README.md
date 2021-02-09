# Data_Structure_From_C
## Queue_4

### malloc()  
  malloc 함수를 사용해 인수로 할당받고자 하는 메모리의 크기를 동적으로 할당 받습니다. 메모리의 크기는 바이트 단위입니다.
  malloc은 메모리 크기에 맞고, 아직 할당되지 않은 적당한 블록을 찾은 뒤 블록의 첫 번째 바이트를 가리키는 주소값을 반환합니다.  
  주소값을 반환받기 때문에 힙 영역에 할당된 메모리 공간으로 접근하려  면 포인터를 사용해야 합니다. 힙 영역에 할당할 수 있는 적당한 블록이 없을 때에는 널 포인터를 반환합니다.  

 
  
  ### free()  
  힙 영역에 할당받은 메모리 공간을 다시 운영체제로 반환해 주는 함수입니다.  
  malloc 함수로 할당 받은 메모리 크기는 런 타임 내내 변화됩니다. 그러므로 free함수를 사용하여 사용이 끝난 메모리를 해제해 주지 않으면, 메모리 누수가 발생할 수 있습니다.

  ### assert()
  예외 처리 함수입니다.  
  주어진 조건식이 참이면 프로그램을 계속 진행하고, 거짓일 경우 오류 메시지 출력과 함께 프로그램을 종료합니다.
  
  ### queue.h
  1. queue의 구조체를 선언합니다.
  2. 동적메모리 할당을 위해 initQueue 에 size 인자를 추가로 받아옵니다. 
  3. 할당받은 메모리를 해제하기 위해 cleanUp 함수를 정의합니다.
  ```c
#ifndef QUEUE_H
#define QUEUE_H

// 구조체 정의
typedef struct 
{
    int *pArr;
    int size;
    int front;
    int rear;
} Queue;

// 함수 원형
int push(Queue * pq, int data);
int pop(Queue * pq);
void initQueue(Queue *pq, int size);
void cleanUp(Queue * pq);
#endif
  ```
  
  ### queue.c
  1. malloc함수로 메모리를 할당받습니다.
  2. 인자로 넘어온 size를 sizeof(int)의 값과 곱한 값이 메모리 크기로 할당됩니다.(q1:400byte, q2:00byte)
  3. free함수로 할당받은 메모리를 반환합니다.
  4. assert함수를 사용하기 위해 전처리문에 assert.h를 추가합니다
  5. assert함수로 pArr에 값이 있을때, 큐가 비었을 때와 꽉찼을 때의 예외처리를 합니다.
  ```c
  #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

void initQueue(Queue *pq, int size)
{
    // 메모리 할당
    pq -> pArr = malloc(sizeof(int)* size);
    // pArr 값이 null 이 아니면 참
    assert(pq->pArr);
    pq ->size = size;
    pq -> front = 0;
    pq -> rear = 0;
}  
void cleanUp(Queue * pq)
{
    free(pq -> pArr);
}
int push(Queue * pq, int data)
{
    // 큐가 꽉 차있으면 프로그램 종료
    assert(pq->rear != pq->size);
    pq->pArr[pq->rear] = data;
    ++pq->rear;

}
int pop(Queue * pq)
{
    // 큐가 비어 있으면 프로그램 종료
    assert(pq->front != pq->rear);
    
    int tmp = pq-> front;
    ++pq->front;
    return pq->pArr[tmp];
}

  ```
  
  ### main.c
  ```c
  #include <stdio.h>
#include "queue.h"

int main (void)
{
    Queue q1, q2;
    
    initQueue(&q1, 100);
    initQueue(&q2, 10);

    push(&q1,100);
    push(&q1,200);
    push(&q1,300);

    printf("q1 1st pop : %d\n",pop(&q1));
    printf("q1 2nd pop : %d\n",pop(&q1));
    printf("q1 3rd pop : %d\n",pop(&q1));
    
    
    push(&q2,900);
    push(&q2,800);
    push(&q2,700);

    printf("q2 1st pop : %d\n",pop(&q2));
    printf("q2 2nd pop : %d\n",pop(&q2));
    printf("q2 3rd pop : %d\n",pop(&q2));

    cleanUp(&q1);
    cleanUp(&q2);

    return 0 ;
}
  ```
   ### 컴파일 및 빌드
```
$ gcc -c main.c  
$ gcc -c queue.c  
$ gcc -o queue main.o queue.o  
$ ./queue.exe
```
### 실행 예시
```
q1 1st pop : 100
q1 2nd pop : 200
q1 3rd pop : 300
q2 1st pop : 900
q2 2nd pop : 800
q2 3rd pop : 700
```
