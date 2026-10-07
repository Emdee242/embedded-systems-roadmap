#include "CircularBuffer.h"
#include <Arduino.h>
void CircularBuffer::write(int x){
buffArray[head] = x;
head = (head + 1) & (size - 1);
if(isFull() != size){
isArrayFull++;
}else if (isFull() == size){
tail = (tail + 1) & (size - 1);
  }
}
int CircularBuffer::read(){
int readVar;
readVar = buffArray[tail];
if(isFull() == 0){
return 0;
}else{
isArrayFull--;
tail = (tail + 1) & (size - 1);
return readVar;
}
}
