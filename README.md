# Data_Structure_From_C
## Linked List4
다양한 자료형에 대응할 수 있도록 앞서 구현한 Linked list를 개선해봅니다. 구조체 타입 변수 포인터에 엘리먼트 사이즈 추가하는 형태로 Linked List 안에 길이정보를 저장합니다.

### list.h
##### Node 구조체 정의
  - 데이터 저장할 공간은 생성하지 않습니다. 
  - 다음을 가리키는 포인터 공간만 생성합니다.
```c
typedef struct node
{
    struct node *next;
} Node;
```
##### List 구조체 정의
  - List 구조체 안에 길이 정보 저장합니다.
  - 노드의 주소값을 담을 포인터를 생성합니다.
  - 각 자료형의 크기에 따라 동적으로 메모리 크기를 설정하기 위한 int형 eleSize 변수를 생성합니다. 
```c
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
  - 더미노드는 데이터가 저장될 공간이 필요 없기 때문에 포인터 공간만 생성합니다. 
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
#### insertFirstNode()함수 구현
  - Node * ptr = malloc(sizeof(Node))시에 힙 상에 포인터 공간만 생성됩니다. 그래서 인자로 받아온 eleSize만큼의 공간을 추가로 할당해 줍니다.
  - 4byte + 4byte 가 됩니다.
  - memcpy를 통해 값을 치환합니다. (목적지, 원본 데이터, 데이터 사이즈)
  - 포인터 + 1 다음 엘리먼트를 가리킵니다. 데이터가 들어갈 위치인 ptr+1은 노드 크기만큼 포인터 공간 뒤에 데이터 공간을 할당합니다. 
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
#### insertNode()함수 구현 
  - ptr의 데이터를 비교하기 위해 memcmp을 사용합니다. (비교할 데이터, 원본데이터, 데이터 사이즈)
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
        Node *tmp = malloc(sizeof(Node)+ plist->elesize);
        assert(tmp );

        memcpy(tmp +1 , pData, pList->eleSize);
        tmp->next = ptr->next;
        ptr->next = tmp;
    }
}

```
#### deleteNode()함수 구현
  - ptr의 데이터를 비교하기 위해 memcmp을 사용합니다. 
```c
void deleteNode(List *pList, const void *pData)
{
    Node *prevPtr = pList->ptr;
    Node *ptr = pList->ptr->next;

    while (ptr )
    {
        if(memcmp(ptr+1, pData, pList->eleSize)== 0)
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
  - 메인에서 출력할수 있는 함수를 받아옵니다.
  - 사용자 정의 연산을 인자로 전달할때 함수 포인터를 사용합니다. 
  
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
##### 임의의 값을 출력하기 위한 printInt , printDouble함수
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
##### initList 함수 
  - 리스트의 주소와 데이터 크기를 전달합니다.
```c
initList(&list1,sizeof(int));
initList(&list2,sizeof(double));
```

##### cleanUpList 함수
  - cleanUp할 리스트의 주소를 전달합니다.
 ```c
cleanUpList(&list1);
cleanUpList(&list2);
 ```
 
##### insertFirstNode 함수
  - 상수를 바로 쓸 수 없습니다.
  - 메모리상에 값이 있어야 하기 떄문에 리스트의 주소값과 데이터의 주소값을 인자로 전달합니다. 
```c
    int i ;
    i = 4;   insertFirstNode(&list1,&i);
    i = 2;  insertFirstNode(&list1, &i);
    i = 1;  insertFirstNode(&list1, &i);
    
    double d;
    d = 4.4;    insertFirstNode(&list2, &d);
    d = 2.2;    insertFirstNode(&list2, &d);
    d = 1.1;    insertFirstNode(&list2, &d);

```
##### insertNode 함수
  - 리스트의 주소값과 prevData의 주소값(j,f), 삽입할 데이터(i,d)의 주소값을 전달합니다.
```c
    int j;
    j = 2;
    i = 3;  
    insertNode(&list1,&j,&i);

    double f;
    f = 2.2;
    d = 3.3;
    insertNode(&list2,&f,&d);
```
##### deleteNode 함수
  - 리스트의 주소값과 삭제할 데이터의 주소값을 전달합니다.
```c
    deleteNode(&list1, &j);
    deleteNode(&list2,&f);
```

##### printList 함수 구현
  - 임의의 값을 출력할 수 있도록 void 포인터 사용자 정의 연산을 만듭니다.
  - 사용자 정의 연산을 인자로 넘기기 위해선 타입이 같아야합니다. 
  - void 포인터는 역참조가 불가능 하기 때문에 본래의 포인터 타입으로 타입케스팅 하여 넘겨줍니다.
```c
void printInt(const void *pData){
    printf("%d", *(int *)pData);
}
void printDouble(const void *pData){
    printf("%f",*(double *)pData);
}
```
#### printList 함수
 - 리스트의 주소값과 리스트의 자료형에 맞는 타입케스팅된 사용자 정의 연산을 넘겨줍니다.
```c
    printList(&list1, printInt);
    printList(&list2, printDouble);

```


### 완성된 main.c
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
