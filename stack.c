
/*
stack이 제대로 동작하려면 허용된 함수만 사용가능해야함
main 에서 접근하지 못하도록 static 사용
내부 구현은 숨기고 인터페이스만 보인다
*/

static int stack[100];
static int tos;    /* top of stack*/ 
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
