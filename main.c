#include <stdio.h>
#include "stack.h"

/*
1. initStack()
2. cleanUpStack()
3. 예외처리 assert()
    - 조건식이 참이면 계속 진행
    - 거짓이면 종료
*/


int main(void)
{
   Stack s1, s2;

    initStack(&s1, 10);
    initStack(&s2, 100);

    push(&s1, 100);
    push(&s1, 200);
    push(&s1, 300);

    push(&s2, 900);
    push(&s2, 800);
    push(&s2, 700);

    printf("s1 1st pop() : %d\n",pop(&s1));
    printf("s1 2nd pop() : %d\n",pop(&s1));
    printf("s1 3rd pop() : %d\n",pop(&s1));

    printf("s2 1st pop() : %d\n",pop(&s2));
    printf("s2 2nd pop() : %d\n",pop(&s2));
    printf("s2 3rd pop() : %d\n",pop(&s2));

    cleanUpStack(&s1);
    cleanUpStack(&s2);

    return 0;
}