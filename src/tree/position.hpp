#ifndef POSITION_HPP
#define POSITION_HPP

template <typename T>
class Position {
public:
    virtual T* getElement() = 0;
};

#endif // !POSITION_HPP