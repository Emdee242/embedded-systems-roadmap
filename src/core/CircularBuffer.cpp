#include "CircularBuffer.h"
#include <Arduino.h>
void CircularBuffer::write(int x) {
    buffArray[head] = x;
    head = (head + 1) & (size - 1);
    if (isArrayFull != size) {
        isArrayFull++;
    } else if (isArrayFull == size) {
        tail = (tail + 1) & (size - 1);
    }
}
int CircularBuffer::read() {
    int readVar;
    readVar = buffArray[tail];
    if (isArrayFull == 0) {
        return 0;
    } else {
        isArrayFull--;
        tail = (tail + 1) & (size - 1);
        return readVar;
    }
}