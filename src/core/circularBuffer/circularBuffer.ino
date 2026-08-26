#include <iostream>
class Buffer{
private:
constexpr static int size = 8;
int buffArray[size];
int head = 0;
int tail = 0;
bool isArrayFull = false;
public:
void write(int x){
  buffArray[head] = x;
  if((tail & (size - 1)) == (head & (size - 1))){
    isArrayFull = true;
  }
  head = (head + 1) & (size - 1);
  
}
int read(){
  int readVar;
  readVar = buffArray[tail];
  if((head & (size - 1)) == (tail & (size - 1))){
    isArrayFull = false;
  }
  if(isFull() == false){
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
void setup(){

}
void loop(){

}