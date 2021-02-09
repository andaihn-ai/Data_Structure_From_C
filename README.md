# Data_Structure_From_C
## Stack5

앞에서 구현한 Stack 4가지의 한계점은 __int__ 자료만 Stack에 구현할 수 있습니다. 하지만 필요에 따라 double, Const char*, short 형 등 다양한 자료형에는 대응이 되지 않는다는 단점이 있습니다. 이번에 구현할 Stack은 다양한 자료형에 대응이 되는 stack을 구현해보도록 할 것입니다.

### stack.h
#### 헤더파일 기초 구조 선언
```c
#ifndef STACK_H
#define STACK_H

/*Source code here*/

#endif
```

#### Stack 구조체 정의
- 구조체에 Stack을 담을 pArr을 선언합니다. 하지만 이전의 stack에서 구현하였던 int형 자료가 아닌 __void*__ 자료형으로 선언을 해주도록 합니다.
- 각 자료형의 크기에 따라 동적으로 메모리의 크기를 설정하기 위해 int형 자료형의 eleSize를 선언합니다.
- 전체 Stack의 사이즈를 지정하기 위해 int형 자료형의 size를 선언합니다.
- stack의 가장 마지막 위치를 저장하기 위해 int형 자료형의 tos를 선언합니다.

```c
typedef struct 
{
    void *pArr;
    int eleSize;
    int size;
    int tos;
} Stack;
```
#### 함수 원형 선언

- 데이터를 담을 Stack을 초기화하는 initStack함수를 선언합니다. 기존의 Stack4에서 사용했던것과 달리 이번에는 함수 인자로 각 요소의 크기를 결정하는 eleSize를 인자로 받습니다.
- Stack을 삭제하기 위한 CleanUpStack 함수를 선언합니다.
- 데이터를 입력할 push 함수를 선언합니다. 입력될 data의 크기는 아직 모르기 때문에 void* 자료형으로 함수 인자를 전달합니다.
- 데이터를 가져올 pop 함수를 선언합니다.

```c
void initStack(Stack* ps, int size,int eleSize);
void cleanUpStack(Stack * ps);
void push(Stack* ps, const void *pData);
void pop(Stack *ps, void *pData);
```

#### 완성된 stack.h
```c
#ifndef STACK_H
#define STACK_H


typedef struct 
{
    void *pArr;
    int eleSize;
    int size;
    int tos;
} Stack;

void initStack(Stack* ps, int size,int eleSize);
void cleanUpStack(Stack * ps);
void push(Stack* ps, const void *pData);
void pop(Stack *ps, void *pData);

#endif
```

### stack.c
#### 필요 헤더 선언

```c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*Source code here*/
```

#### initStack()함수 구현

우선 initStack의 return은 없기 때문에 __void initStack()__ 을 사용합니다. 그리고 다양한 자료형에 대응되는 Stack을 초기화 하기 위해서는 다음과 같은 변수가 필요합니다.
- Stack을 생성할 메모리 주소값
- 전체 Stack 배열의 크기
- 원하는 자료형의 크기

위의 3가지 변수를 함수에서 입력받은 후 초기화를 실행합니다.
- Stack을 담을 pArr을 초기화합니다. 이 때 __자료형의 크기 x 전체 배열의 크기__ 그기만큼 memory allocation 함수(malloc()함수)를 선언하여 크기를 할당해줍니다.
- 정상적으로 Stack 메모리가 설정되었는지 디버깅 하기 위해 assert()함수를 사용하여 확인합니다.
- Stack에 담을 자료형의 크기를 Stack 구조체의 eleSize에 담아놓습니다.
- Stack의 전체 크기를 담을 size를 Stack 구조체의 size에 담아놓습니다.
- Stack의 가장 마지막 위치인 tos를 0으로 초기화 합니다.

```c
void initStack(Stack* ps, int size,int eleSize)
{
    ps -> pArr = malloc(eleSize * size);
    assert(ps->pArr);
    ps->eleSize = eleSize;
    ps->size = size;
    ps->tos = 0;
}
```

#### cleanUpStack()함수 구현

Stack을 메모리에서 삭제하는 cleanUpStack()을 구현하기 위해서는 다음과 같은 변수를 인자로 받습니다.
- Stack의 메모리 주소값

다음 인자를 받아서 free() 함수를 사용해 메모리 할당을 제거하면 됩니다.

```c
void cleanUpStack(Stack * ps)
{
    free(ps->pArr);
}
```

#### push()함수 구현
Stack에 자료를 입력하는 push() 함수의 return값은 없기 때문에 __void__ 를 사용합니다. push 함수를 구현하기 위해서는 다음과 같은 인자가 필요합니다.
- Stack의 메모리 주소값 Stack* ps
- Stack에 저장할 데이터 const void* pData. 이때 데이터의 크기는 아직 모르는 상황이고 입력받은 자료형을 읽기만 해야하기 떄문에 __const void*__ 자료형으로 인자를 받아야 합니다.

함수로 인자를 받았다면 우선 입력작업을 수행하기 전 Stack에 할당되어 있는 용량이 가득차있는지 확인이 필요합니다. 이를 위해 assert() 함수를 사용하여 Stack의 tos와 size를 비교하여 같은 값이면 Stack의 메모리 용량이 가득차있기 때문에 에러가 발생하도록 디버깅을 수행합니다.

아직 Stack의 메모리 공간이 남아있다면 입력받은 pData를 Stack에 입력하도록 합니다. 이때 Stack에 순차적으로 데이터를 쌓기 위해 바이트 단위로 값을 불러와 입력을 해야 합니다. 이를 위해 memory copy 함수(memcpy())를 사용하여 입력받은 데이터를 Stack에 저장하도록 합니다.

memcpy()가 완료되었다면 Stack의 tos값을 1 증가시키도록 합니다.

```c
void push(Stack *ps, const void *pData)
{ 
    assert(ps->tos != ps->size);

    /*memcpy(&ps->pArr[ps->tos],pData, ps->eleSize); X 역참조 불가*/
    memcpy((unsigned char *)ps->pArr + ps->eleSize * ps->tos,pData,ps->eleSize);
    ++ps->tos;
}
```


#### pop()함수 구현
Stack에서 자료를 읽어오는 pop()함수의 경우 기존에는 정해진 자료형이 있었기 때문에 해당 자료형의 값으로 return을 수행해주면 되었다. 하지만 다양한 자료형에 맞게 데이터를 불러오기 위해서는 각각 자료형에 맞는 return값을 구현할 수 없기 때문에 __void__ 를 사용합니다. pop() 함수를 구현하기 위해서는 다음과 같은 인자를 받아야 합니다.
- 자료를 가져올 Stack의 포인터값.
- 가져올 자료를 담아넣을 변수 pData. 이때 pData의 자료형은 아직 알 수 없기 떄문에 void* 를 사용합니다.

자료를 가져오기 전 기존의 Stack에 자료가 하나도 없는 경우가 있을 수 있습니다. 이럴 경우를 확인하기 위해 assert() 함수를 사용하여 tos가 0인지를 확인해 볼 필요가 있습니다.

정상적으로 데이터가 포함되어 있는 경우라면 Stack의 tos를 1 감소시킨 후 push와 동일하게 바이트 단위로 데이터를 읽어와 자료를 저장할 pData에 memcpy() 함수를 사용하여 복사를 수행합니다.

```c
void pop(Stack *ps, void *pData)
{
    assert(ps->tos != 0);

    --ps->tos;
    /*memcpy(pData, &ps->pArr[ps->tos], ps->eleSize); X 역참조 불가능*/
    memcpy(pData,(unsigned char*)ps->pArr + ps->eleSize * ps->tos, ps->eleSize);
}
```

#### 완성된 stack.c
```c
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void initStack(Stack* ps, int size,int eleSize)
{
    ps -> pArr = malloc(eleSize * size);
    assert(ps->pArr);
    ps->eleSize = eleSize;
    ps->size = size;
    ps->tos = 0;
}

void cleanUpStack(Stack * ps)
{
    free(ps->pArr);
}

void push(Stack *ps, const void *pData)
{ 
    assert(ps->tos != ps->size);

    memcpy((unsigned char *)ps->pArr + ps->eleSize * ps->tos,pData,ps->eleSize);
    ++ps->tos;
}

void pop(Stack *ps, void *pData)
{
    assert(ps->tos != 0);

    --ps->tos;
    memcpy(pData,(unsigned char*)ps->pArr + ps->eleSize * ps->tos, ps->eleSize);
}
```

### main.c
다양한 변수를 선언 후 Stack 두가지를 선언하여 값을 입력해보고 가져오는 예제를 구현합니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void)
{
   Stack s1, s2;

    initStack(&s1, 10, sizeof(int));
    initStack(&s2, 100, sizeof(double));

    int i;
    i = 100; push(&s1,&i);
    i = 200; push(&s1,&i);
    i = 300; push(&s1,&i);


    double d;
    d = 1.1; push(&s2, &d);
    d = 2.2; push(&s2, &d);
    d = 3.3; push(&s2, &d);
   
    int j;
    pop(&s1, &j); printf("s1 1st pop() : %d\n",j);
    pop(&s1, &j); printf("s1 2nd pop() : %d\n",j);
    pop(&s1, &j); printf("s1 3rd pop() : %d\n",j);
   
   double f;
    pop(&s2, &f); printf("s1 1st pop() : %f\n",f);
    pop(&s2, &f); printf("s1 2nd pop() : %f\n",f);
    pop(&s2, &f); printf("s1 3rd pop() : %f\n",f);
    
   
    cleanUpStack(&s1);
    cleanUpStack(&s2);

    return 0;
}
```

### 컴파일 및 빌드
```bash
$ gcc -c main.c  
$ gcc -c stack.c  
$ gcc -o stack main.o stack.o  
$ ./stack.exe
```

### 실행 예시
```bash
s1 1st pop() : 300
s1 2nd pop() : 200
s1 3rd pop() : 100
s1 1st pop() : 3.300000
s1 2nd pop() : 2.200000
s1 3rd pop() : 1.100000
```