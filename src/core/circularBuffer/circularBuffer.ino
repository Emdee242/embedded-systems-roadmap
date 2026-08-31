class Buffer{
private:
constexpr static int size = 1024;
int buffArray[size];
int head = 0;
int tail = 0;
uint16_t isArrayFull = 0;
public:
void write(int x){
buffArray[head] = x;
head = (head + 1) & (size - 1);
if(isFull() != size){
isArrayFull++;
}else if (isFull() == size){
tail = (tail + 1) & (size - 1);
  }
}
int read(){
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
int isFull() const{
return isArrayFull;
}
};
void setup(){

}
void loop(){

}