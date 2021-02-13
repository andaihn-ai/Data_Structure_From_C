# Data_Structure_From_C
## Linked List2
구현한 Linked List 다음 단계는 모듈화하기 입니다.
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다.

  list.h/list.c/main.c로 나누어 모듈화 합니다
  - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
  - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다.


### list.h 
  - 전처리문 입니다. 
```c
#ifndef LIST_H
#define LIST_H
/*
  source code
*/
#endif
```
  - 연결리스트의 노드 구조체 입니다. 데이터를 저장할 맴버와 다음노드를 가리킬 포인터를 정의합니다. 구조체 포인터를 담은 List 구조체 입니다. 우리는 List 구조체를 이용해 연결리스트를 구현할 것 입니다. 
```c
typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct
{
    Node *ptr;
} List;
```
  - 함수 선언문입니다. 초기화 함수, 모든 노드를 삭제하는 함수, 첫번째 노드를 생성하는 함수, 삽입,삭제 함수, 리스트를 출력하는 함수입니다. 
```c
void initList(List *pList);
void cleanUpList(List *pList);

void insertFirstNode(List *pList, int data);
void insertNode(List *pList, int prevData, int data);
void deleteNode(List *pList, int data);

void printList(const List *pList);
```
### 완성된 list.h
```c
#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct
{
    Node *ptr;
} List;


void initList(List *pList);
void cleanUpList(List *pList);

void insertFirstNode(List *pList, int data);
void insertNode(List *pList, int prevData, int data);
void deleteNode(List *pList, int data);

void printList(const List *pList);

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
  1. 리스트 초기화 함수입니다.  헤드 노드에 8바이트를 할당한뒤 마지막 노드를 생성합니다. 헤드 노드(head node)는 단일 연결 리스트의 기준점이며 헤드(head)라고도 부릅니다. 머리 노드는 첫 번째 노드를 가리키는 용도이므로 데이터를 저장하지 않습니다. 동적할당으로 선언된 최초의 노드는 어떠한 값도 포함하고 있지 않기 때문에 null로 초기화 해주는 작업이 필요합니다. 
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
  5. 원하는 노드를 삭제하는 함수입니다. 인자값으로 데이터를 받아와 일치하는 데이터가 있는경우 해당 노드를 삭제하기 위해 그 노드가 가지고있던 다음 노드 주소를 삭제할 이전노드의 next로 가리킵니다. 해당 노드의 메모리 할당을 해제하여 삭제할 수 있습니다.
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
```
  6. 존재하는 리스트의 값을 출력하는 함수입니다. 
```c
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
### 완성된 list.c
```c
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initList(List *pList)
{
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);

    pList->ptr->next = NULL;
}

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

void insertFirstNode(List *pList, int data)
{
    Node *ptr = malloc(sizeof(Node));
    assert(ptr );

    ptr->data = data;
    ptr->next = pList->ptr->next;
    pList->ptr->next = ptr;

}

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
  
```c
#include <stdio.h>
#include "list.h"

int main(void)
{
    List list;
    initList(&list);

    insertFirstNode(&list,4);   
    insertFirstNode(&list,3);   
    insertFirstNode(&list,1);  

    insertNode(&list,1,2); 

    deleteNode(&list,3);   

    printList(&list); 

    cleanUpList(&list);    
    
    printList(&list);
    return 0;    
}
```

### 컴파일 및 빌드
```
$ gcc -c main.c
$ gcc -c list.c
$ gcc -o list main.o list.o
$ gcc ./list.exe
```
### 실행예시
```

```
