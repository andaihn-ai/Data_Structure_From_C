#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


void initStack(Stack* s)
{
    s->tos = 0;
}

void push(Stack* s, int data)
{
    /*
    꽉 차있으면 프로그램 중단
    */
    
    if (s->tos == ARRAYSIZE)
    {
        printf(stderr,"stack is full\n");
        exit(1);
    }
    s->array[s->tos] = data;
    ++s->tos;
}

int pop(Stack* s)
{
    /*
    비어있으면 프로그램 중단
    */

   if(s->tos ==0)
   {
       printf(stderr,"stack is empty\n");
       exit(2);
   }
    --s->tos;
    return s->array[s->tos];
}


