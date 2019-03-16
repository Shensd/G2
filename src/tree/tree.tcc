#include "tree.hpp"

template<class T>
Tree<T>::Tree() {}

template<class T>
void Tree<T>::setRoot(T value) {
    if(!rootSet) {
        Node n(nullptr, nullptr, nullptr, value);
        root = n;

        rootSet = true;
    }
}