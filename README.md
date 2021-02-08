# Data_Structure_From_C
## Stack_2
구현한 Stack의 다음 단계는 모듈화하기 입니다.  
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.  

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다. 
  
  main.c/ stack.c/ stack.h 로 나누어 모듈화 합니다.  

> - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
> - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다. 


### stack.h
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
