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