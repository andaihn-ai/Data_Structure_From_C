#ifndef STACK_H
#define STACK_H
#define ARRAYSIZE 100

/* 구조체는 헤더파일에 들어간다*/

typedef struct 
{
    int array[ARRAYSIZE];
    int tos;
} Stack;

void initStack(Stack* stack);
void push(Stack* s, int data);
int pop(Stack* s);

#endif