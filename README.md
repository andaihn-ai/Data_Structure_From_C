# Data_Structure_From_C
## stack_4
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
  

### stack.h
  1. 할당받은 메모리를 해제하기 위해 cleanUpStack 함수를 정의합니다.
```c
#ifndef STACK_H
#define STACK_H

typedef struct 
{
    int *pArr;
    int size;
    int tos;
} Stack;

void initStack(Stack* stack, int size);
void cleanUpStack(Stack * s);
void push(Stack* s, int data);
int pop(Stack* s);

#endif
```

### stack.c
  1. malloc으로 메모리를 할당받습니다.
  2. 인자로 넘어온 size를 sizeof(int)의 값과 곱한 값이 메모리 크기로 할당됩니다.
```c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initStack(Stack* s,int size)
{
    s->pArr = malloc(sizeof(int)*size);
    assert(s->pArr /*!= NULL*/);
    s->size = size;
    s->tos = 0;
}
void cleanUpStack(Stack * s)
{
    free(s->pArr);
}
void push(Stack* s, int data)
{ 
    assert(s->tos != s->size);
    s->pArr[s->tos] = data;
    ++s->tos;
}

int pop(Stack* s)
{
    assert(s->tos != 0);
    --s->tos;
    return s->pArr[s->tos];
}

```
