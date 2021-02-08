# Data_Structure_From_C
## stack_4
  1. malloc()  
  
  malloc 함수를 사용해 인수로 할당받고자 하는 메모리의 크기를 동적으로 할당 받습니다. 메모리의 크기는 바이트 단위입니다.
  malloc은 메모리 크기에 맞고, 아직 할당되지 않은 적당한 블록을 찾은 뒤 블록의 첫 번째 바이트를 가리키는 주소값을 반환합니다. 주소값을 반환받기 때문에 힙 영역에 할당된 메모리 공간으로 접근하려  면 포인터를 사용해야 합니다. 힙 영역에 할당할 수 있는 적당한 블록이 없을 때에는 널 포인터를 반환합니다.  

 
  
  2. free()  
  
  힙 영역에 할당받은 메모리 공간을 다시 운영체제로 반환해 주는 함수입니다. 
  malloc 함수로 할당 받은 메모리 크기는 런 타임 내내 변화됩니다. 그러므로 free함수를 사용하여 사용이 끝난 메모리를 해제해 주지 않으면, 메모리 누수가 발생할 수 있습니다.
assert 
