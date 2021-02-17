# Data_Structure_From_C
## Linked List2
구현한 Linked List 다음 단계는 모듈화하기 입니다.
보통 파일 단위로 나누어 프로그램을 구성하는 요소의 일부를 관련된 데이터와 함수들을 묶어서 모듈을 형성합니다.

하나의 프로그램을 작성할때 이식성과 확장성이 좋도록 기능별로 나누는 작업입니다. 이 파일들은 개별 컴파일된 후, 링커에 의해 하나의 실행 파일로 만들어집니다.

  list.h/list.c/main.c로 나누어 모듈화 합니다
  - .h 파일은 구현할 함수의 원형(Prototype)을 정의합니다.
  - .c 파일은 .h 파일에서 정의한 함수의 기능을 구현합니다.


### list.h 
  ##### 전처리문 입니다. 
```c
#ifndef LIST_H
#define LIST_H
/*
  source code
*/
#endif
```
  ##### 연결리스트의 노드 구조체 
  - 데이터를 저장할 맴버와 다음노드를 가리킬 포인터를 정의합니다. 
```c
typedef struct node
{
    int data;
    struct node *next;
} Node;
```
##### 더미노드 구조체
  - 삽입과 삭제를 위한 더미노드입니다.
```c
typedef struct
{
    Node *ptr;
} List;
```

##### 함수 선언문
  - 초기화 함수, 모든 노드를 삭제하는 함수, 맨 앞(첫번째)의 노드를 생성하는 함수, 삽입,삭제 함수, 리스트를 출력하는 함수입니다. 
  - printList 함수는 안의 내용을 바꾸지 않기 때문에 const List * pList 자료형 입니다. 
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
  ##### initLIst 함수 구현
  - 리스트 초기화 함수입니다. 
  - ptr 은 더미노드를 가리키는 포인터 입니다. 
  - 더미노드안의 데이터는 필요 없고, 포인터는 널을 가리킵니다.
```c
void initList(List *pList)
{
    pList->ptr = malloc(sizeof(Node));
    assert(pList->ptr);

    pList->ptr->next = NULL;
}
```
##### cleanUpList 함수 구현
  - 
  - 모든 노드를 삭제하는 함수입니다.
  - 노드가 존재할시 임시변수 tmp를 사용해 while문을 돌며 메모리 할당을 해제해 줍니다.
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
##### insertFirstNode 함수 구현
  - 첫번째(맨앞) 노드를 생성하는 함수입니다.
  - 첫번째 노드의 링크 필드를 initList()로 생성한 마지막 노드를 가리킵니다.
  - malloc으로 노드를 하나 만듭니다.
  - ptr이 널이 아닌지 체크해줍니다.
  - ptr의 데이터에는 인자값으로 포인터 리스트와 정수형 데이터를 받아와 데이터 필드에 넣어줍니다.
  - ptr->next에는 더미노드에 있는 next를 복사해 옵니다.
  - 더미노드의 포인터는 ptr의 데이터를 가리킵니다.
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
##### insertNode 함수 구현
  - 노드를 원하는 위치에 삽입하는 함수입니다. 
  - 인자값으로 리스트의 주소와 삽입하고자 하는 위치의 노드 데이터값, 삽입하고자 하는 데이터 값을 받아옵니다. 
  - 값이 있는 노드를 가리키는 ptr을 생성합니다.
  - ptr이 널이 아닌 경우 반복문을 돌려 prevData와 일치하는 데이터가 있으면 반복문을 종료합니다. 반복문이 종료되는 경우는 데이터를 찾거나 찾는 데이터가 없지만 리스트가 끝나 ptr이 널이 되는 경우입니다. 
  - 반복문의 결과(ptr->next)를 ptr에 저장해 줍니다.
  - 반복문 종료후 ptr이 널이 아닌 경우는 데이터를 찾은 것입니다. 이 경우 tmp 노드를 만들어 tmp의 데이터에 삽입하고자 하는 데이터를 넣어줍니다.
  - 이전 노드의 포인터(ptr->next)는 tmp 를 가리킵니다.
  - tmp의 포인터는 ptr->next(이전 노드의 포인터가 가리키는 데이터)를 가리킵니다. 
  - ptr->next(이전 노드의 포인터) 는 tmp를 가리킵니다.
  - 찾는 데이터가 없는 경우 아무것도 실행되지 않습니다. 
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
##### deleteNode 함수 구현
  - 원하는 노드를 삭제하는 함수입니다. 
  - 인자값으로 리스트의 주소와 삭제하고자 하는 위치의 노드 데이터값을 받아옵니다. 
  - 더미노드를 가리키는 prevPtr을 생성합니다.
  - 실제 값이 있는 데이터를 가리키는 ptr을 생성합니다. 
  - 반복문을 돌려 ptr과 prevPtr을 다음노드로 이동시킵니다.
  - 일치하는 데이터가 있는경우 반복문을 종료합니다. 
  - ptr에 값이 있는경우 해당 노드를 삭제하기 위해 그 노드가 가지고있던 다음 노드를 삭제할 이전노드(prevData)의 포인터(prevData->next)로 가리킵니다. 
  - 해당 노드의 메모리 할당을 해제하여 삭제할 수 있습니다.
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
##### printList 함수 구현
  - 존재하는 리스트의 값을 출력하는 함수입니다. 
  - 실제 값이 있는 노드를 가리키는 ptr을 생성합니다.
  - 
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
##### 전처리문
```c
#include <stdio.h>
#include "list.h"
```
##### 리스트 초기화
  - 구조체 자료를 넘기기 위해 주소값으로 넘깁니다. 
```c
List list;
initList(&list);
```

##### insertFirstNode 함수
  - 맨 앞쪽에 노드 삽입
  - 인자로 리스트의 주소값과 데이터를 넘깁니다. 

```c
 insertFirstNode(&list,4);   
 insertFirstNode(&list,3);   
 insertFirstNode(&list,1);  
```
##### insertNode 함수
  - 원하는 위치에 노드 삽입
  - 기준이 되는 노드 뒤에 원하는 데이터 값의 노드를 삽입합니다.
  - 인자로 리스트 주소, 기준이 되는 노드의 데이터값, 삽입하고자 하는 노드의 데이터값을 넘깁니다. 
  ```c
 insertNode(&list,1,2); 
  ```
##### deleteNode 함수
  - 값을 찾아서 삭제
  - 인자로 리스트의 주소와 삭제하고자 하는 노드의 데이터값을 넘깁니다.
```c
deleteNode(&list,3); 
```
##### cleanUPList 함수
  - 모든 노드를 삭제
  - 인자로 리스트의 주소값을 넘깁니다. 
```c
cleanUpList(&list)
```

### 완성된 main.c
  
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
[1,2,4]
[]
```
