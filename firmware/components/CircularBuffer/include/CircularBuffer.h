#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include <cassert>
#include <optional>
class CircularBuffer {
  private:
    static constexpr int size = 1024;
    static_assert(((size & (size - 1)) == 0) && size != 0);
    int buffArray[size]{};
    int head = 0;
    int tail = 0;
    int isArrayFull = 0;

  public:
    void write(int x);
    std::optional<int> read();
    int isFull() const { return isArrayFull; }
};
#endif
