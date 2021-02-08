# Data_Structure_From_C
## Stack_3
모듈화한 스택을 메모리상에 여러개의 스택을 사용하여 내가 원하는 자료를 찍어내기 위해 구조체를 사용합니다.  
구조체는 기본 타입만으로는 나타낼 수 없는 복잡한 데이터를 표현할 수 있습니다.   
배열이 같은 타입의 변수 집합이라고 한다면, 구조체는 다양한 타입의 변수 집합을 나타냅니다. 이때 구조체를 구성하는 변수를 맴버변수 라고 합니다.  
### stack.h
#### 구조체 정의
  1. 구조체는 헤더파일에 들어갑니다.
  2. 매크로 함수로 ARRAYSIZE 를 정의합니다.
  3. 지역변수이기 떄문에 init 함수를 구현하여 초기화를 해주어야 합니다.
  4. 구조체에 접근하기 위해 포인터 인자를 사용합니다. 
 
```c
#ifndef STACK_H
#define STACK_H
#define ARRAYSIZE 100

typedef struct 
{
    int array[ARRAYSIZE];
    int tos;
} Stack;

void initStack(Stack* stack);
void push(Stack* s, int data);
int pop(Stack* s);

#endif
```
### main.c
#### 구조체 사용
  1. 
```c
#include <stdio.h>
#include "stack.h"

int main(void)
{
   Stack s1, s2;

    initStack(&s1);
    initStack(&s2);

    push(&s1, 100);
    push(&s1, 200);
    push(&s1, 300);

    push(&s2, 900);
    push(&s2, 800);
    push(&s2, 700);

    printf("s1 1st pop() : %d\n",pop(&s1));
    printf("s1 2nd pop() : %d\n",pop(&s1));
    printf("s1 3rd pop() : %d\n",pop(&s1));

    printf("s2 1st pop() : %d\n",pop(&s2));
    printf("s2 2nd pop() : %d\n",pop(&s2));
    printf("s2 3rd pop() : %d\n",pop(&s2));

    pop(&s1);

    return 0;
}
```
### stack.c
```c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


void initStack(Stack* s)
{
    s->tos = 0;
}

void push(Stack* s, int data)
{
    /*
    꽉 차있으면 프로그램 중단
    */
    
    if (s->tos == ARRAYSIZE)
    {
        printf(stderr,"stack is full\n");
        exit(1);
    }
    s->array[s->tos] = data;
    ++s->tos;
}

int pop(Stack* s)
{
    /*
    비어있으면 프로그램 중단
    */

   if(s->tos ==0)
   {
       printf(stderr,"stack is empty\n");
       exit(2);
   }
    --s->tos;
    return s->array[s->tos];
}



```



### 컴파일 및 빌드
##### main.c 와 stack.c 를 각각 컴파일 한 뒤 실행파일을 만들어줍니다.
```
$ gcc -c main.c  
$ gcc -c stack.c  
$ gcc -o stack main.o stack.o  
$ ./stack.exe
```
### 실행 예시
```
s1 1st pop() : 300
s1 2nd pop() : 200
s1 3rd pop() : 100
s2 1st pop() : 700
s2 2nd pop() : 800
s2 3rd pop() : 900
```
