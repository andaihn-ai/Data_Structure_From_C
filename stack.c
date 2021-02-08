#include <stdio.h>

/*

데이터가 들어갈 배열 
1. 초기화 -> but 전역변수는 초기화 가능하기 떄문에 따로 안해주어도 됨

2. 마지막 데이터 위치를 알아낼 변수(전역변수) 
> push와 pop이 둘다 접근 하기 위해
*/

int stack[100];
int tos;    /* top of stack*/ 
void push(int data)
{
    stack[tos] = data;
    ++tos;
}
int pop(void)
{
    --tos;
    return stack[tos];
}

int main(void)
{
    push(100);
    push(200);
    push(300);

    printf("1st pop() : %d\n",pop());
    printf("2nd pop() : %d\n",pop());
    printf("3rd pop() : %d\n",pop());
    return 0;
}