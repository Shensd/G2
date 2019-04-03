#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <vector>

template <typename T>
class Queue {
private:
    std::vector<T> list;

    const int DEFAULT_CAPACITY = 32;

    int maxSize;
    int size = 0;
    int front = 0;

public:
    Queue(int maxSize);
    Queue(void);

    void enqueue(T element);
    T dequeue(void);

    T getTop(void);
    bool isEmpty(void);
    int getSize(void);
};

#include "queue.tcc"

#endif // !QUEUE_HPP