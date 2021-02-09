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