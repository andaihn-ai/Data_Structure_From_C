# Data_Structure_From_C
## Linked List3
Linked List2에이어 노드를 생성하는 코드가 반복되는것을 개선-> createNode()함수를 구현해 봅니다. 
### list.h
##### createNode 함수 원형
 - 반복되는 list.c 의 노드 생성 코드를 함수화 합니다.
 - 현재 만든 노드의 주소값을 반환합니다.
 - 인자로 int형 데이터와 포인터의 값은 바뀌지 않기 때문에 const 노드타입의 포인터 next를 받습니다.
 - static을 사용해 list와 관련된 함수들만 노드를 만들고, main에서 사용하지 못하도록 합니다.
```c
static Node *createNode(int data, const Node *next);
```

### 완성된list.h
```c
#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct{
    Node *ptr;
} List;

static Node *createNode(int data, const Node *next);

void initList(List *pList);
void cleanUpList(List *pList);

void insertFirstNode(List *pList, int data);
void insertNode(List *pList, int prevData, int data);
void deleteNode(List *pList, int data);

void printList(const List *pList);

#endif 
```
### list.c
##### create함수 구현
  - 노드타입의 포인터를 넘겨주는 createNode함수 입니다.
  - const속성을 없애고 (Node * )로 타입 케스팅을 해줍니다. 
  
```c
static Node *createNode(int data, const Node *next)
{
    Node *ptr = malloc(sizeof(Node));
    assert(ptr );

    ptr->data = data;
    ptr->next = (Node *)next;

}
```
##### initList 함수 구현
  - 더미노드이지만 값이 무조건 필요하기 때문에 아무 의미없는 -1을 데이터로 넘겨줍니다.
  - 포인터에는 null을 넘겨 줍니다.
```c
void initList(List *pList)
{
   
    pList->ptr = createNode(-1,NULL);
}
```

##### insertFirstNode 함수 구현
  - 맨앞의 더미노드의 next가 새로운 노드를 가리킵니다.
  - 새로운 노드의 next는 원래의 더미노드가 가지고 있던 next를 가리킵니다.
```c
void insertFirstNode(List *pList, int data)
{
   
    pList->ptr->next = createNode(data,pList->ptr->next);

}
```
##### insertNode 함수 구현
  - ptr의 next에 새로운 노드의 데이터와 다음 노드를 가리키는 ptr->next를 넣습니다.
```c
void insertNode(List *pList, int prevData, int data)
{
   
    Node *ptr = pList->ptr->next;

    while(ptr ){
        if (ptr->data == prevData)
            break;
        ptr = ptr->next;
    }

    if(ptr ){
        
        ptr->next = createNode(data,ptr->next);
    }
}
```
### 완성된 list.c
```c
static Node *createNode(int data, const Node *next)
{
    Node *ptr = malloc(sizeof(Node));
    assert(ptr );

    ptr->data = data;
    ptr->next = (Node *)next;

}
void initList(List *pList)
{
   
    pList->ptr = createNode(-1,NULL);
}

void cleanUpList(List *pList)
{
    Node *ptr = pList->ptr;
    while(ptr)
    {
        Node* tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    pList->ptr = NULL;
}

void insertFirstNode(List *pList, int data)
{
   
    pList->ptr->next = createNode(data,pList->ptr->next);

}

void insertNode(List *pList, int prevData, int data)
{
   
    Node *ptr = pList->ptr->next;

    while(ptr ){
        if (ptr->data == prevData)
            break;
        ptr = ptr->next;
    }

    if(ptr ){
        
        ptr->next = createNode(data,ptr->next);
    }
}

void deleteNode(List *pList, int data)
{
    Node *prevPtr = pList->ptr;
    Node *ptr = pList->ptr->next;

    while (ptr )
    {
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

    printList(&list);

    insertNode(&list,1,2);
    printList(&list);

    deleteNode(&list,3);
    printList(&list);

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
[1,3,4]
[1,2,3,4]
[1,2,4]
```
