#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void initStack(Stack* s,int size)
{
    s->pArr = malloc(sizeof(int)*size);
    assert(s->pArr /*!= NULL*/);
    s->size = size;
    s->tos = 0;
}
void cleanUpStack(Stack * s)
{
    free(s->pArr);
}
void push(Stack* s, int data)
{ 
    assert(s->tos != s->size);
    s->pArr[s->tos] = data;
    ++s->tos;
}

int pop(Stack* s)
{
    assert(s->tos != 0);
    --s->tos;
    return s->pArr[s->tos];
}


