#include <stdio.h>
#include "stack.h"

/*
1. 메모리상에 내가 원하는 자료를 찍어내기
-> 사용자 정의형 구조체
-> 여러개의 스택 사용하기

2. 인자를 사용하여 원하는 스택에 값을 넣는다.
------------------------------------------
3. 지역변수를 쓰면 초기화 안됨

4. init함수 사용하여 초기화

5. 함수 인자로 포인터 사용

 구조체에 접근하는 포인터 연산자 ->
*/


int main(void)
{
   Stack s1, s2;

    initStack(&s1);
    initStack(&s2);

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

    pop(&s1);

    return 0;
}