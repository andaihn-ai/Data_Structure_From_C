# Data_Structure_From_C
## Linked List4

### list.h
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
