#ifndef CIRCULARBUFFER_CPP
#define CIRCULARBUFFER_CPP

#include "CircularBuffer.h"

template <typename T>
CircularBuffer<T>::CircularBuffer(std::size_t size)
    : max(size), tail(0), length(0), buffer{new T[size]}
{
}

template <typename T>
void CircularBuffer<T>::reset()
{
    length = 0;
    tail = 0;
}

template <typename T>
bool CircularBuffer<T>::isFull()
{
    return length == max;
}

template <typename T>
size_t CircularBuffer<T>::len()
{
    return length;
}

template <typename T>
void CircularBuffer<T>::enQueue(T item)
{
    buffer[tail] = item;
    if (tail == 0)
        tail = max - 1;
    else
        tail = tail - 1;

    if (length < max)
        length = length + 1;
}

template <typename T>
T CircularBuffer<T>::deQueue()
{
    size_t head = (tail + length) % max;
    if (length > 0)
        length = length - 1;
    return buffer[head];
}

template <typename T>
T CircularBuffer<T>::reduce(const std::function<T(T, T)> &op)
{
    T res;
    size_t i, curr;

    curr = (tail + 1) % max;
    res = buffer[curr];
    i = 1;
    while (i < length)
    {
        curr = (curr + 1) % max;
        res = op(res, buffer[curr]);
        i = i + 1;
    }

    return res;
}

#endif