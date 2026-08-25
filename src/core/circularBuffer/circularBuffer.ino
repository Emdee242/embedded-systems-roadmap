class Buffer{
private:
int size = 1024;
int buffArray[size];
int head = 0;
int tail = 0;
public:
if(head == tail){
head = (head + 1) & (size - 1);
}
int write(){
  
}
};
