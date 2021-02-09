#Linked List1
  - 빈번하게 삽입 삭제가 이루어지기 때문에 필요할때 메모리를 할당하는 형태로 만드는 것이 적절하다. 
  - 노드는 |데이터| + |포인터| 의 구조이다.
  - 노드는 데이터를 갖고있는 데이터 필드와 리스트의 다음 노드의 주소를 갖고있는 포인터로 구성된다.
## list.c
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
