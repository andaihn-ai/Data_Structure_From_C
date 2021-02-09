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
