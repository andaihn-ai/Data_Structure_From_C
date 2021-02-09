#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void initStack(Stack* ps, int size,int eleSize)
{
    ps -> pArr = malloc(eleSize * size);
    assert(ps->pArr);
    ps->eleSize = eleSize;
    ps->size = size;
    ps->tos = 0;
}

void cleanUpStack(Stack * ps)
{
    free(ps->pArr);
}

void push(Stack *ps, const void *pData)
{ 
    assert(ps->tos != ps->size);

    /*memcpy(&ps->pArr[ps->tos],pData, ps->eleSize); X 역참조 불가*/
    memcpy((unsigned char *)ps->pArr + ps->eleSize * ps->tos,pData,ps->eleSize);
    ++ps->tos;
}

void pop(Stack *ps, void *pData)
{
    assert(ps->tos != 0);

    --ps->tos;
    /*memcpy(pData, &ps->pArr[ps->tos], ps->eleSize); X 역참조 불가능*/
    memcpy(pData,(unsigned char*)ps->pArr + ps->eleSize * ps->tos, ps->eleSize);
}


