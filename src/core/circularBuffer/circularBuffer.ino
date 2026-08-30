#include <iostream>
class Buffer{
private:
constexpr static int size = 8;
int buffArray[size];
int head = 0;
int tail = 0;
bool isArrayFull = false;
public:
bool write(int x){
  if(((head + 1) & (size - 1)) == ((tail) & (size - 1))){
    isArrayFull = true;
    return false;
    
  }else{
    buffArray[head] = x;
    head = (head + 1) & (size - 1);
    isArrayFull = false;
    return true;
  }
}
int read(){
  int readVar;
    readVar = buffArray[tail];  
  if(isArrayFull == false && ((head) & (size - 1)) == ((tail) & (size - 1))){
    return 0;
  }else{
    tail = (tail + 1) & (size - 1);
    return readVar;
  }
  
  
}
bool isFull() const{
  return isArrayFull;
}
};