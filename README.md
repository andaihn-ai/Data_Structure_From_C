# Data_Structure_From_C
## Stack_2
구현한 Stack의 다음 단계는 모듈화하기 입니다.  
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.  

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다. 
  
  main.c/ stack.c/ stack.h 로 나누어 모듈화 합니다.  

> - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
> - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다. 

### main.c
```c
#include <stdio.h>
#include "stack.h"

int main(void)
{
    push(100);
    push(200);
    push(300);

    printf("1st pop() : %d\n",pop());
    printf("2nd pop() : %d\n",pop());
    printf("3rd pop() : %d\n",pop());
    return 0;
}
```

### stack.h
```c
#ifndef STACK_H
#define STACK_H

void push(int data);
int pop(void);

#endif
```

### stack.c
```c
static int stack[100];
static int tos;    /* top of stack*/ 
void push(int data)
{
    stack[tos] = data;
    ++tos;
}
int pop(void)
{
    --tos;
    return stack[tos];
}
```

### 컴파일 및 빌드
##### main.c 와 stack.c 를 각각 컴파일 한 뒤 실행파일을 만들어줍니다.

  $ gcc -c main.c  
$ gcc -c stack.c  
$ gcc -o stack main.o stack.o  
$ ./stack.exe

### 실행 예시
1st pop() : 300  
2nd pop() : 200  
3rd pop() : 100
