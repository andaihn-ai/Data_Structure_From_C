#include <stdio.h>
#include <stdlib.h>
/*
    1. queue 는 일종의 버퍼의 개념
    2. FIFO형태(first in first out)넣어논 데이터를 차례대로 사용한다.
    3. 데이터 삽입, 데이터 추출 변수가 필요하다.

*/

int queue[10];
int front;
int rear;

int push(int data)
{
    queue[rear] = data;
    ++rear;

}
int pop(void)
{
    int tmp = front;
    ++front;
    return queue[tmp];
}

int main (void)
{
    push(100);
    push(200);
    printf("1st pop : %d\n",pop());

    push(300);
    printf("2nd pop : %d\n",pop());
    printf("3rd pop : %d\n",pop());
    

    return 0 ;
}