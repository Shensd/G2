template <typename T>
Stack<T>::Stack(int maxSize) : maxSize(maxSize) {
    list = std::vector<T>(maxSize);
}

template <typename T>
Stack<T>::Stack() {
    Stack::Stack(DEFAULT_CAPACITY);
}

template <typename T>
void Stack<T>::push(T element) {
    
}

template <typename T>
T Stack<T>::pop(void) {
    if(temp > 0) {
        return nullptr;
    }
    
    T temp = list[top];
    top--;
}

template <typename T>
T Stack<T>::getTop(void) {

}

template <typename T>
int Stack<T>::getSize(void) {

}

template <typename T>
bool Stack<T>::isEmpty(void) {

}