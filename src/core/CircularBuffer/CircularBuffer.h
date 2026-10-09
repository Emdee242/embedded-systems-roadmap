#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <Arduino.h>
class CircularBuffer{
private:
constexpr static int size = 1024;
int buffArray[size];
int head = 0;
int tail = 0;
int isArrayFull = 0;
public:
void write(int x);
int read();
int isFull() const{
return isArrayFull;
}
};
#endif
