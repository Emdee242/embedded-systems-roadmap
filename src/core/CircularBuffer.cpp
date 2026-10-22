#include "CircularBuffer.h"
#include <cassert>
#include <optional>
void CircularBuffer::write(int x) {
    assert(head <= 1023);
    buffArray[head] = x;
    head = (head + 1) & (size - 1);
    if (isArrayFull != size) {
        isArrayFull++;
    } else if (isArrayFull == size) {
        tail = (tail + 1) & (size - 1);
    }
    assert(isArrayFull <= 1024);
}
std::optional<int> CircularBuffer::read() {
    int readVar;
    assert(tail <= 1023);
    readVar = buffArray[tail];
    if (isArrayFull == 0) {
        return 0;
    } else {
        isArrayFull--;
        tail = (tail + 1) & (size - 1);
        return readVar;
    }
    assert(isArrayFull <= 1024);
}