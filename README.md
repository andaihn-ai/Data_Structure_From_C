# Data_Structure_From_C
## Linked List4
다양한 자료형에 대응할 수 있도록 앞서 구현한 Linked list를 개선해봅니다. 

### list.h
##### List 구조체 정의
  - Linked List 구조체 안에 길이 정보 저장
  - 노드의 주소값을 담을 포인터
  - 각 자료형의 크기에 따라 동적으로 메모리 크기를 설정하기 위한 int형 eleSize
```c
typedef struct node
{
    struct node *next;
} Node;

typedef struct{
    Node *ptr;
    int eleSize;

} List;
```
### 함수 원형 선언
  - 리스트를 초기화 하는 initList의 함수 인자로 각 요소의 크기를 결정하는 eleSize를 인자로 받습니다.
  - insertFirstNode를 비롯한 insertNode 와 deleteNode함수는 입력될 data의 크기는 아직 모르기 때문에 void* 자료형으로 함수 인자를 전달합니다. 또한 포인터가 가리키는 값은 바뀌지 않기 때문에 const void * 자료형이 됩니다.
  - printList함수는 ~~~
```c
void initList(List *pList, int eleSize);
void cleanUpList(List *pList);

void insertFirstNode(List *pList, const void *pData);
void insertNode(List *pList, const void *pPrevData, const void *pData);
void deleteNode(List *pList, const void *pData);

void printList(const List *pList, void(*print)(const void *pData));

```
### 완성된 list.h
```c
#ifndef LIST_H
#define LIST_H

typedef struct node
{
    struct node *next;
} Node;

typedef struct{
    Node *ptr;
    int eleSize;

} List;


void initList(List *pList, int eleSize);
void cleanUpList(List *pList);

void insertFirstNode(List *pList, const void *pData);
void insertNode(List *pList, const void *pPrevData, const void *pData);
void deleteNode(List *pList, const void *pData);

void printList(const List *pList, void(*print)(const void *pData));

#endif
```

### list.c
##### initList() 함수 구현
  - 더미노드는 데이터가 저장될 공간이 필요 없기 때문에 포인터 공간만 남겨줍니다. 
```c
void initList(List *pList, int eleSize)
{
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);

    pList->ptr->next = NULL;
    pList-> eleSize = eleSize;
}

```
##### cleanUp()함수 구현
```c
void cleanUpList(List *pList)
{
    Node * ptr = pList->ptr;
    while(ptr ){
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}
```
##### insertFirstNode()함수 구현
  - Node * ptr = malloc(sizeof(Node))시에 힙 상에 포인터 공간만 생성됩니다. 그래서 인자로 받아온 eleSize만큼의 공간을 추가로 할당해 줍니다.
  - 4byte + 4byte 가 됩니다.
  - memcpy를 통해 값을 치환합니다. 
  - 포인터 공간 뒤에 데이터 공간을 할당합니다. 이것은 ptr + 1로 표현됩니다. 
```c
void insertFirstNode(List *pList, const void *pData)
{
    Node *ptr = malloc(sizeof(Node)+pList->eleSize);
    assert(ptr );

    memcpy(ptr+1, pData, pList->eleSize);
    ptr->next = pList->ptr->next;
    pList->ptr->next = ptr;

}
```
##### insertNode()함수 구현 
  - ptr의 데이터를 비교하기 위해 memcmp을 사용합니다. 
  - 데이터 치환을 위해 memcpy를 사용합니다. 
```c
void insertNode(List *pList, const void *pPrevData, const void *pData)
{
    /*해당하는 prevData 가 있으면 뒤에 삽입*/
    Node *ptr = pList->ptr->next;
    while(ptr ){
        if(memcmp(ptr+1 , pPrevData, pList->eleSize)==0)
            break;
        ptr = ptr->next;
    }
    if(ptr ){
        Node *tmp = malloc(sizeof(Node));
        assert(tmp );

        memcpy(tmp +1 , pData, pList->eleSize);
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
}

```
##### deleteNode()함수 구현
  - ptr의 데이터를 비교하기 위해 memcmp을 사용합니다. 
  - 데이터 치환을 위해 memcpy를 사용합니다. 
```c
void deleteNode(List *pList, const void *pData)
{
    Node *prevPtr = pList->ptr;
    Node *ptr = pList->ptr->next;

    while (ptr )
    {
        if(memcmp(ptr+1, pData, pList->eleSize)==0)
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
##### printList()함수 구현
  - 임의의 값(int형 리스트와 double형 리스트)을 출력하는 함수이다.
  - 사용자 정의 연산을 인자로 전달할때 함수 포인터를 사용합니다. 
  - 
```c
void printList(const List *pList, void(*print)(const void *pData))
{
    Node *ptr = pList->ptr->next;

    printf("[");
    while(ptr ){
        (*print)(ptr + 1);  /*print(ptr + 1)*/
        
        printf((ptr->next )?", ":"");
        ptr = ptr->next;
    }
    printf("]\n");
}

```
### 완성된 list.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

void initList(List *pList, int eleSize)
{
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);

    pList->ptr->next = NULL;
    pList-> eleSize = eleSize;
}

void cleanUpList(List *pList)
{
    Node * ptr = pList->ptr;
    while(ptr ){
        Node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void insertFirstNode(List *pList, const void *pData)
{
    Node *ptr = malloc(sizeof(Node)+pList->eleSize);
    assert(ptr );

    memcpy(ptr+1, pData, pList->eleSize);
    ptr->next = pList->ptr->next;
    pList->ptr->next = ptr;

}

void insertNode(List *pList, const void *pPrevData, const void *pData)
{
    /*해당하는 prevData 가 있으면 뒤에 삽입*/
    Node *ptr = pList->ptr->next;
    while(ptr ){
        if(memcmp(ptr+1 , pPrevData, pList->eleSize)==0)
            break;
        ptr = ptr->next;
    }
    if(ptr ){
        Node *tmp = malloc(sizeof(Node));
        assert(tmp );

        memcpy(tmp +1 , pData, pList->eleSize);
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
}

void deleteNode(List *pList, const void *pData)
{
    Node *prevPtr = pList->ptr;
    Node *ptr = pList->ptr->next;

    while (ptr )
    {
        if(memcmp(ptr+1, pData, pList->eleSize)==0)
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

void printList(const List *pList, void(*print)(const void *pData))
{
    Node *ptr = pList->ptr->next;

    printf("[");
    while(ptr ){
        (*print)(ptr + 1);  /*print(ptr + 1)*/
        
        printf((ptr->next )?", ":"");
        ptr = ptr->next;
    }
    printf("]\n");
}
```
### main.c
##### 임의의 값을 출력하기 위한 함수
  - 반환타입과 인자 타입이 같기 때문에 같은 함수에 전달할 수 있습니다. 
```c
void printInt(const void *pData){
    printf("%d", *(int *)pData);
}
void printDouble(const void *pData){
    printf("%f",*(double *)pData);
}
```
##### 출력함수 인자 전달
```c
  printList(&list1, printInt);
  printList(&list2, printDouble);
```

##### 함수 사용 부분
  - 메모리상에 값이 있어야 하기 때문에 주소값을 인자로 줍니다.
  - 
```c
int main(void)
    List list1, list2;

    initList(&list1,sizeof(int));
    initList(&list2,sizeof(double));

    int i ;
    i= 4;   insertFirstNode(&list1,&i);

    i = 2;  insertFirstNode(&list1, &i);
    i = 1;  insertFirstNode(&list1, &i);

    int j;
    j = 2;

    i = 3;  insertNode(&list1,&j,&i);

    deleteNode(&list1, &j);

    printList(&list1, printInt);

    double d;
    d = 4.4;    insertFirstNode(&list2, &d);
    d = 2.2;    insertFirstNode(&list2, &d);
    d = 1.1;    insertFirstNode(&list2, &d);

    double f;
    f = 2.2;
    d = 3.3;
    insertNode(&list2,&f,&d);
    
    deleteNode(&list2,&f);

    printList(&list2, printDouble);

    cleanUpList(&list1);
    cleanUpList(&list2);
    return 0;

    
}
```
