# Data_Structure_From_C
## Stack_1
stack의 첫번째 구현은 전역구역에 int형 자료를 담을 배열을 선언하고 해당 배열에서 값을 입력하는 push 함수와 값을 가져오는 pop 함수를 구현하는 것입니다.

int형 100개의 자료를 담을 stack이라는 이름의 배열을 선언한다. 그리고 stack의 가장 위의 원소위치를 확인하기 위한 tos를 선언한다. 해당 변수들은 전역변수로 선언하기 때문에 자동 초기화되어 따로 초기화 작업은 필요 없다.

```c
#include <stdio.h>

int stack[100];
int tos;
```

stack에 자료를 입력하게 위해 push 함수를 구현한다. stack 배열의 tos 위치에 데이터를 삽입하고 함수 종료 시 tos값을 1 상승시킨다.

```c
void push(int data)
{
    stack[tos] = data;
    ++tos;
}
```

다음은 stack에서 자료를 가져오는 pop 함수를 구현한다. pop 함수의 리턴값은 int형 자료형이고, tos값을 1 감소시킨 뒤 stack 배열의 tos위치에 있는 값을 리턴해준다.

```c
int pop(void)
{
    --tos;
    return stack[tos];
}
```

정상적으로 잘 구현되었는지 main 함수를 작성한다.

```c
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

main까지 작성되었다면 저장 후 컴파일 및 빌드를 수행한다.

```bash
$ gcc -c stac.c
$ gcc -o stack stack.o
$ ./stack.exe
```

__실행예시__

```bash
1st pop() : 300
2nd pop() : 200
3rd pop() : 100
```