# Data_Structure_From_C
## Queue3
메모리상에 여러개의 큐을 사용하여 내가 원하는 자료를 찍어내기 위해 구조체를 사용합니다.
구조체는 기본 타입만으로는 나타낼 수 없는 복잡한 데이터를 표현할 수 있습니다.
배열이 같은 타입의 변수 집합이라고 한다면, 구조체는 다양한 타입의 변수 집합을 나타냅니다. 이때 구조체를 구성하는 변수를 맴버변수 라고 합니다.

### queue.h
##### 구조체 정의
  1. 구조체는 헤더파일에 들어갑니다.
  2. 매크로 함수로 ARRAYSIZE 를 정의합니다.
  3. 지역변수이기 떄문에 init 함수를 구현하여 초기화를 해주어야 합니다.
  4. 구조체에 접근하기 위해 포인터 인자를 사용합니다.
  
  ```c
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
  ```
  
 ### queue.c
 ##### initStack 함수 구현과 push/pop 함수 성능 개선
  1. 맴버변수 front와 rear의 값을 초기화 해줍니다.
  2. 큐가 꽉 차있을때 push 하지 못하도록 프로그램을 종료할 수 있게 개선합니다.
  3. 큐가 비어있으면 pop 하지 못하도록 프로그램을 종료할 수 있게 개선합니다.
 ```c
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

 ```
 
 ### main.c
 ##### 구조체 사용
  1. 구조체를 사용해 q1, q2 를 선언해 준 뒤 동작시켜 봅니다.
 ```c
#include <stdio.h>
#include "queue.h"

int main (void)
{
    Queue q1, q2;
    /* Queue queues[10]; */
    /*
    q1.front = q1.rear = 0;
    q2.front = q2.rear = 0;
    */

    initQueue(&q1);
    initQueue(&q2);

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
