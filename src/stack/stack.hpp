#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> list;

    const int DEFAULT_CAPACITY = 32;

    int top = 0;
    int maxSize;
public:
    Stack(int maxSize);
    Stack();

    void push(T);
    T pop(void);

    T getTop(void);
    int getSize(void);
    bool isEmpty(void);
};

#include "stack.tcc"

#endif // !STACK_HPP