# Data_Structure_From_C
## Linked List4
다양한 자료형에 대응할 수 있도록 앞서 구현한 Linked list를 개선해봅니다. 

### list.h
##### List 구조체 정의
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
  - insertFirstNode를 비롯한 insertNode 와 deleteNode함수는 입력될 data의 크기는 아직 모르기 때문에 void* 자료형으로 함수 인자를 전달합니다.
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
```c
#include <stdio.h>
#include "list.h"

void printInt(const void *pData){
    printf("%d", *(int *)pData);
}
void printDouble(const void *pData){
    printf("%f",*(double *)pData);
}

int main(void)
{
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
