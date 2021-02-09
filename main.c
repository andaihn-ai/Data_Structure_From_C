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