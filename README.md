# Data_Structure_From_C
## Queue_1

큐(Queue)는 일종의 버퍼의 개념입니다.  
Queue의 첫번째 구현은 전역구역에 int형 자료를 담을 배열을 선언하고 해당 배열에서 값을 입력하는 push 함수와 값을 가져오는 pop 함수를 구현하는 것입니다.

int형 10개의 자료를 담을 queue이라는 이름의 배열을 선언합니다. 그리고 queue의 데이터 삽입을 위한 rear 변후와 데이터 추출을 위한 front변수를 선언합니다. 해당 변수들은 전역변수로 선언하기 때문에 자동 초기화되어 따로 초기화 작업은 필요 없습니다.

### queue.c
```c
#include <stdio.h>
#include <stdlib.h>

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
```

### 컴파일 및 빌드
```
$ gcc -c queue.c
$ gcc -o queue queue.o
$ gcc ./queue.exe
```
### 실행예시
```
1st pop : 100
2nd pop : 200
3rd pop : 300
```
