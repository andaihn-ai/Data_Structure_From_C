# Data_Structure_From_C
## Linked List1
  - 빈번하게 삽입 삭제가 이루어지기 때문에 필요할때 메모리를 할당하는 형태로 만드는 것이 적절합니다. 
  - 노드는 데이터 + 포인터의 구조입니다.
  - 노드는 데이터를 갖고있는 데이터 필드와 리스트의 다음 노드의 주소를 갖고있는 포인터로 구성됩니다.
### list.c

##### 구조체 정의
  - 하나의 정수값과 포인터를 갖는 구조체를 선언합니다. 
```c
typedef struct 
{
    int data;
    struct node *next;
} Node;
```

##### 연결리스트 생셩
```c
    Node *ptr;
    ptr = malloc(sizeof(Node));     /*8byte 할당*/

    /* linked list 생성 */
    ptr->data = 1;
    ptr->next =  malloc(sizeof(Node)); 
    ptr->next->data = 3;
    ptr->next->next =  malloc(sizeof(Node)); 
    ptr->next->next->data = 4;
    ptr->next->next->next = NULL;
```
##### 중간에 노드 삽입
```c
    /* 2번 삽입 */
    Node *tmp =  malloc(sizeof(Node)); 
    tmp ->data = 2;
    tmp->next = ptr->next;
    ptr->next = tmp;
```
##### 노드 삭제
```c
    /*3 번 삭제*/
    tmp = ptr->next->next;
    ptr->next->next = tmp->next;
    free(tmp);

    Node *p = ptr;
```    
##### 노드 출력
```c
    while (p)
    {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
```
##### 모든 노드 삭제
```c
    /* 모두삭제 */
    p = ptr;
    while(p){
        /* 임시변수를 이용해 삭제할 노드를 임시변수에 담아놓고 다음을 가르킨뒤 임시변수를 삭제한다. */
        Node *tmp = p;
        p = p->next;
        free(tmp);
    }

    return 0 ;
}
```

##### 완성된 list.c
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int data;
    struct node *next;
} Node;


int main(void)
{
    Node *ptr;
    ptr = malloc(sizeof(Node));     /*8byte 할당*/

    /* linked list 생성 */
    ptr->data = 1;
    ptr->next =  malloc(sizeof(Node)); 
    ptr->next->data = 3;
    ptr->next->next =  malloc(sizeof(Node)); 
    ptr->next->next->data = 4;
    ptr->next->next->next = NULL;

    /* 2번 삽입 */
    Node *tmp =  malloc(sizeof(Node)); 
    tmp ->data = 2;
    tmp->next = ptr->next;
    ptr->next = tmp;
    
    /*3 번 삭제*/
    tmp = ptr->next->next;
    ptr->next->next = tmp->next;
    free(tmp);

    Node *p = ptr;
    while (p)
    {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
    /* 모두삭제 */
    p = ptr;
    while(p){
        /* 임시변수를 이용해 삭제할 노드를 임시변수에 담아놓고 다음을 가르킨뒤 임시변수를 삭제한다. */
        Node *tmp = p;
        p = p->next;
        free(tmp);
    }

    return 0 ;
}
```
