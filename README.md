# Data_Structure_From_C
## Linked List3

### list.h
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
