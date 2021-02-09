# Data_Structure_From_C
자료구조를 C를 통해 학습합니다.  
Stack / Queue / Linked List 를 단계적으로 생성해 봅니다.

## Goal
  - 큐(Queue)의 기본 연산을 이해합니다.
  - C로 큐(Queue)를 구현할 수 있습니다.
  
## 큐(Queue)의 개념
  - 큐에는 선형과 환형이 있습니다.
  - 선형은 막대 모양으로 된 큐입니다. 크기가 제한되어있고 빈 공간을 사용하려면 모든 자료를 꺼내거나 자료를 한칸씩 옮겨야 한다는 단점이 있습니다.
  - 배열의 한쪽 에서는 삽입, 다른 한쪽에서는 추출이 이루어짐으로 먼저 넣은 데이터가 먼저 나오는 FIFO(First In First Out) 구조입니다.
  
 ## 큐(Queue)의 연산
 큐는 push(insert)와 pop(delete)을 이용하여 구현됩니다. push는 큐에 자료를 넣는 것을, pop은 큐에서 자료를 꺼내는 것을 의미합니다. front(head)와 rear(tail)는 데이터의 위치를 가리킵니다.  
 front는 데이터를 pop할 수 있는 위치를, rear은 데이터를 push할 수 있는 위치를 의미합니다.  
   
   큐가 꽉 차서 더 이상 자료를 넣을 수 없는 경우(push 할 수 없는 경우)를 오버플로우(Overflow), 큐가 비어 있어 자료를 꺼낼 수 없는 경우(pop 할 수 없는 경우)를 언더플로우(Underflow)라고 합니다.
