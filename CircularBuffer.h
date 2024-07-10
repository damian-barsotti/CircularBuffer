#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <cstddef>
#include <functional>

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(std::size_t size);
    void enQueue(T item);
    T deQueue();
    bool isFull();
    size_t len();
    T reduce(const std::function<T(T, T)> &op);
    void reset();

private:
    T *buffer;
    std::size_t tail, length, max; // of the buffer
};

#include "CircularBuffer.cpp"

#endif
