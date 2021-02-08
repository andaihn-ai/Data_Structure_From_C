#ifndef STACK_H
#define STACK_H


/* 구조체는 헤더파일에 들어간다*/

typedef struct 
{
    int *pArr;
    int size;
    int tos;
} Stack;

void initStack(Stack* stack, int size);
void cleanUpStack(Stack * s);
void push(Stack* s, int data);
int pop(Stack* s);

#endif