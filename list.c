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
