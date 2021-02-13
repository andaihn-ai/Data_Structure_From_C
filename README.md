# Data_Structure_From_C
## Linked List2
구현한 Linked List 다음 단계는 모듈화하기 입니다.
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다.

  list.h/list.c/main.c로 나누어 모듈화 합니다
  - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
  - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다.


### queue.h
```c
#ifndef QUEUE_H
#define QUEUE_H

int push(int data);
int pop(void);

#endif
```

### list.c
  - 필요한 헤더파일을 불러옵니다.
  ```c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

  ```
  - 정의한 함수의 기능을 구현합니다.
  1. 리스트 초기화 함수입니다.  헤더 포인터에 8바이트를 할당한뒤 마지막 노드를 생성합니다.
```c
void initList(List *pList)
{
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);

    pList->ptr->next = NULL;
}
```
  2. 모든 노드를 삭제하는 함수입니다. 노드가 존재할시 임시변수 tmp를 사용해 while문을 돌며 메모리 할당을 해제해 줍니다.
```c
void cleanUpList(List *pList)
{
    Node * ptr = pList->ptr;
    while(ptr ){
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    pList->ptr = NULL;
}
```
  3. 첫번째 노드를 생성하는 함수입니다. 인자값으로 포인터 리스트와 정수형 데이터를 받아와 데이터 필드에 넣어줍니다. 첫번째 노드의 링크 필드를 initList()로 생성한 마지막 노드를 가리킵니다.
```c
void insertFirstNode(List *pList, int data)
{
    Node *ptr = malloc(sizeof(Node));
    assert(ptr );

    ptr->data = data;
    ptr->next = pList->ptr->next;
    pList->ptr->next = ptr;

}
```
  4. 노드를 원하는 위치에 삽입하는 함수입니다. 인자값으로 삽입하고자 하는 위치의 노드 데이터값을 받아옵니다. 일치하는 데이터가 있는 경우 다음 노드자리에 삽입됩니다. 임시변수를 사용해 일치하는 데이터의 링크필드를 임시변수를 가리키도록 합니다. 임시변수의 링크필드를 다음노드를 가리키도록 합니다. 
```c
void insertNode(List *pList, int prevData, int data)
{
    /*해당하는 prevData 가 있으면 뒤에 삽입*/
    Node *ptr = pList->ptr->next;
    while(ptr ){
        if (ptr->data == prevData)
            break;
        ptr = ptr->next;
    }
    if(ptr ){
        Node *tmp = malloc(sizeof(Node));
        assert(ptr );

        tmp->data = data;
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
}
```
  5. 원하는 노드를 삭제하는 함수입니다. 인자값으로 데이터를 받아와 일치하는 데이터가 있는경우 
```c
void deleteNode(List *pList, int data)
{
    Node *prevPtr = pList->ptr;
    Node *ptr = pList->ptr->next;

    while (ptr )
    {
        /* code */
        if(ptr->data == data)
        
            break;
        
        ptr = ptr->next;
        prevPtr = prevPtr->next;
    }
    if(ptr )
    {
        prevPtr->next = ptr->next;
        free(ptr);
    }
    
}

void printList(const List *pList)
{
    Node *ptr;
    if(pList->ptr)
        ptr = pList->ptr->next;
    else
        ptr = NULL;

    printf("[");
    while(ptr ){
        
        printf("%d", ptr->data);
        printf((ptr->next )?", ":"");
        ptr = ptr->next;
    }
    printf("]\n");
}
```

### main.c
  1. 큐의 동작을 확인합니다.
```c
int main (void)
{
    push(100);
    push(200);
    printf("1st pop : %d\n",pop());

    push(300);
    printf("2nd pop : %d\n",pop());
    printf("3rd pop : %d\n",pop());
    

    return 0 ;
}
```

### 컴파일 및 빌드
```
$ gcc -c main.c
$ gcc -c queue.c
$ gcc -o queue main.o queue.o
$ gcc ./queue.exe
```
### 실행예시
```
1st pop : 100
2nd pop : 200
3rd pop : 300
```
