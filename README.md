# Data_Structure_From_C
## Queue5


앞에서 구현한 Queue 4가지의 한계점은 __int__ 자료만 Queue 구현할 수 있습니다. 하지만 필요에 따라 double, Const char*, short 형 등 다양한 자료형에는 대응이 되지 않는다는 단점이 있습니다. 이번에 구현할 Queue 다양한 자료형에 대응이 되는 Queue 구현해보도록 할 것입니다.

### Queue.h
#### 헤더파일 기초 구조 선언
```c
#ifndef QUEUE_H
#define QUEUE_H

/*Source code here*/

#endif
```

#### Queue 구조체 정의
- 구조체에 Queue 담을 pArr을 선언합니다. 하지만 이전의 Queue 구현하였던 int형 자료가 아닌 __void*__ 자료형으로 선언을 해주도록 합니다.
- 각 자료형의 크기에 따라 동적으로 메모리의 크기를 설정하기 위해 int형 자료형의 eleSize를 선언합니다.
- 전체 Queue 사이즈를 지정하기 위해 int형 자료형의 size를 선언합니다.
- Queue에 데이터 삽입 위치를 저장하기 위해 int형 자료형의 rear를 선언합니다.
- Queue에 데이터 추출 위치를 저장하기 위해 int형 자료형의 front를 선언합니다.

```c
typedef struct 
{
    void *pArr;
    int eleSize;
    int size;
    int front;
    int rear;
} Queue;
```
#### 함수 원형 선언

- 데이터를 담을 Queue 초기화하는 initQueue 선언합니다. 기존의 Queue4에서 사용했던것과 달리 이번에는 함수 인자로 각 요소의 크기를 결정하는 eleSize를 인자로 받습니다.
- Queue를 삭제하기 위한 CleanUp 함수를 선언합니다.
- 데이터를 입력할 push 함수를 선언합니다. 입력될 data의 크기는 아직 모르기 때문에 void* 자료형으로 함수 인자를 전달합니다.
- 데이터를 가져올 pop 함수를 선언합니다.

```c
void initQueue(Queue *pq, int size, int eleSize);
void cleanUp(Queue * pq);

void push(Queue * pq, const void *pData);
void pop(Queue * pq, void *pData);

```

#### 완성된 queue.h
```c
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
```

### stack.c
#### 필요 헤더 선언

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

/*Source code here*/
```

#### initQueue()함수 구현

우선 initQueue의 return은 없기 때문에 __void initQueue()__ 을 사용합니다. 그리고 다양한 자료형에 대응되는 Queue를 초기화 하기 위해서는 다음과 같은 변수가 필요합니다.
- Queue를 생성할 메모리 주소값
- 전체 Queue 배열의 크기
- 원하는 자료형의 크기

위의 3가지 변수를 함수에서 입력받은 후 초기화를 실행합니다.
- Queue를 담을 pArr을 초기화합니다. 이 때 __자료형의 크기 x 전체 배열의 크기__ 그기만큼 memory allocation 함수(malloc()함수)를 선언하여 크기를 할당해줍니다.
- 정상적으로 Queue 메모리가 설정되었는지 디버깅 하기 위해 assert()함수를 사용하여 확인합니다.
- Queue에 담을 자료형의 크기를 Queue 구조체의 eleSize에 담아놓습니다.
- Queue의 전체 크기를 담을 size를 Queue 구조체의 size에 담아놓습니다.
- Queue의 삽입 위치인 rear를 0으로 초기화 합니다.
- Queue의 추출 위치인 front를 0으로 초기화 합니다.

```c
void initQueue(Queue *pq, int size, int eleSize)
{
    pq -> pArr = malloc(eleSize* size);
    
    assert(pq->pArr);

    pq -> eleSize = eleSize;
    pq ->size = size;
    pq -> front = 0;
    pq -> rear = 0;
} 
```

#### cleanUp()함수 구현

Queue을 메모리에서 삭제하는 cleanUp()을 구현하기 위해서는 다음과 같은 변수를 인자로 받습니다.
- Queue의 메모리 주소값

다음 인자를 받아서 free() 함수를 사용해 메모리 할당을 제거하면 됩니다.

```c
void cleanUp(Queue * pq)
{
    free(pq -> pArr);
}
```

#### push()함수 구현
Queue에 자료를 입력하는 push() 함수의 return값은 없기 때문에 __void__ 를 사용합니다. push 함수를 구현하기 위해서는 다음과 같은 인자가 필요합니다.
- Queue의 메모리 주소값 Queue* ps
- Queue에 저장할 데이터 const void* pData. 이때 데이터의 크기는 아직 모르는 상황이고 입력받은 자료형을 읽기만 해야하기 떄문에 __const void*__ 자료형으로 인자를 받아야 합니다.

함수로 인자를 받았다면 우선 입력작업을 수행하기 전 Queue에 할당되어 있는 용량이 가득차있는지 확인이 필요합니다. 이를 위해 assert() 함수를 사용하여 Queue의 rear와 size를 비교하여 같은 값이면 Queue의 메모리 용량이 가득차있기 때문에 에러가 발생하도록 디버깅을 수행합니다.

아직 Queue의 메모리 공간이 남아있다면 입력받은 pData를 Queue에 입력하도록 합니다. 이때 Queue에 순차적으로 데이터를 쌓기 위해 바이트 단위로 값을 불러와 입력을 해야 합니다. 이를 위해 memory copy 함수(memcpy())를 사용하여 입력받은 데이터를 Queue에 저장하도록 합니다.

memcpy()가 완료되었다면 Queue의 rear값을 1 증가시키도록 합니다.

```c
void push(Queue * pq, const void *pData)
{
    assert(pq->rear != pq->size);
    /* memcpy(&pq->pArr[pq->rear],pData,pq->eleSize); */
    memcpy( (unsigned char*)&pq->pArr + pq->eleSize * pq->rear, pData, pq->eleSize);
    ++pq->rear;

}
```


#### pop()함수 구현
Queue에서 자료를 읽어오는 pop()함수의 경우 기존에는 정해진 자료형이 있었기 때문에 해당 자료형의 값으로 return을 수행해주면 되었습니다. 하지만 다양한 자료형에 맞게 데이터를 불러오기 위해서는 각각 자료형에 맞는 return값을 구현할 수 없기 때문에 __void__ 를 사용합니다. pop() 함수를 구현하기 위해서는 다음과 같은 인자를 받아야 합니다.
- 자료를 가져올 Queue의 포인터값.
- 가져올 자료를 담아넣을 변수 pData. 이때 pData의 자료형은 아직 알 수 없기 떄문에 void* 를 사용합니다.

자료를 가져오기 전 기존의 Queue에 자료가 하나도 없는 경우가 있을 수 있습니다. 이럴 경우를 확인하기 위해 assert() 함수를 사용하여 front가 rear와 같은 값인지를 확인해 볼 필요가 있습니다.

정상적으로 데이터가 포함되어 있는 경우라면 임시변수 tmp에 front 값을 넣고, Queue의 font를 1 증가시킨 후 push와 동일하게 바이트 단위로 데이터를 읽어와 자료를 저장할 pData에 memcpy() 함수를 사용하여 복사를 수행합니다.

```c
void pop(Queue * pq, void *pData)
{
    assert(pq->front != pq->rear);
    
    int tmp = pq-> front;
    ++pq->front;
    
    memcpy( pData, (unsigned char*)&pq->pArr + pq->eleSize * tmp, pq->eleSize);
}
```

#### 완성된 queue.c
```c
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
    memcpy( (unsigned char*)&pq->pArr + pq->eleSize * pq->rear, pData, pq->eleSize);
    ++pq->rear;

}
void pop(Queue * pq, void *pData)
{
    assert(pq->front != pq->rear);
    
    int tmp = pq-> front;
    ++pq->front;
    
    memcpy( pData, (unsigned char*)&pq->pArr + pq->eleSize * tmp, pq->eleSize);
}

```

### main.c
다양한 변수를 선언 후 Queue 두가지를 선언하여 값을 입력해보고 가져오는 예제를 구현합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main (void)
{
    Queue q1, q2;
    
    initQueue(&q1, 100, sizeof(int));
    initQueue(&q2, 10, sizeof(double));

    int i;
    
    i = 100; push(&q1, &i);
    i = 200; push(&q1, &i);
    i = 300; push(&q1, &i);

    int j;

    pop(&q1, &j);  printf("q1 1st pop : %d\n",j);
    pop(&q1, &j);  printf("q1 2nd pop : %d\n",j);
    pop(&q1, &j);  printf("q1 3rd pop : %d\n",j);    
    
    double d;
    d = 1.1; push(&q2,&d);
    d = 2.2; push(&q2,&d);
    d = 3.3; push(&q2,&d);
   

    double f;
    pop(&q2, &f);  printf("q2 1st pop : %d\n",f);
    pop(&q2, &f);  printf("q2 2nd pop : %d\n",f);
    pop(&q2, &f);  printf("q2 3rd pop : %d\n",f);    
    
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
q2 1st pop : 1.100000
q2 2nd pop : 2.200000
q2 3rd pop : 3.300000
`
