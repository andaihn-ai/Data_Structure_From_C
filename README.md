# Data_Structure_From_C
## Stack_2
구현한 Stack의 다음 단계는 모듈화하기 입니다.  
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.  

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다. 
  
  main.c/ stack.c/ stack.h 로 나누어 모듈화 합니다.  

    - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
    - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다. 

### stack.h
#### 조건부 컴파일 
    1. #if
    #if 지시자 다음에 나오는 조건식의 결과가 0이 아니면 참, 0이면 거짓으로 간주합니다. 참일 경우 컴파일 합니다.
    2. #ifdef
    if defined 라는 문장을 줄여서 만든 것으로, 여러개의 헤더파일을 작성한 후에 같은 이름의 변수나 함수가 중복으로 선언되어 있을 가능성이 있습니다. 이러한 경우 #ifdef 지시자를 사용하여 중복 선언의 가능성을 제거해 줍니다. 
    3. #ifndef
    if not defined 라는 문장을 줄여서 만든 것으로, 정의되어 있지 않은 헤더파일의 경우를 정의해 줄때 사용합니다. 만약 매크로 이름과 같은 헤더파일이 정의되어 있으면 그냥 넘어갈 것입니다. 
    4. #endif
    조건부 컴파일의 끝을 명시합니다.

```c
#ifndef STACK_H
#define STACK_H

void push(int data);
int pop(void);

#endif
```

### main.c
#### 헤더파일 include
> 1. #include "stack.h"
>> 같은 디렉토리 안의 사용자 정의 헤더파일을 불러옵니다.
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

### stack.c
#### push/pop 함수의 기능 구현
> 다른 파일에서 접근이 불가능 하도록 static 키워드로 정적변수 선언을 합니다. 
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
```
$ gcc -c main.c  
$ gcc -c stack.c  
$ gcc -o stack main.o stack.o  
$ ./stack.exe
```
### 실행 예시
```
1st pop() : 300  
2nd pop() : 200  
3rd pop() : 100
```
