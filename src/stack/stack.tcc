template <typename T>
Stack<T>::Stack(int maxSize) : maxSize(maxSize) {
    list = std::vector<T>(maxSize);
    list.reserve(maxSize);
}

template <typename T>
Stack<T>::Stack() {
    Stack::Stack(DEFAULT_CAPACITY);
}

/**
 * Push a given element to the top of the stack
 * 
 * @param element element to push onto stack
 */
template <typename T>
void Stack<T>::push(T element) {
    if(getSize() >= maxSize) throw new std::runtime_error("Attempted to push element but stack is full.");

    list[top] = element;
    top++;
}

/**
 * Remove the top item from the stack and return it
 * 
 * @return top item of stack 
 */
template <typename T>
T Stack<T>::pop(void) {
    if(top-1 < 0) throw new std::runtime_error("Attempted to pop but stack is empty");
    
    T temp = list[top-1];
    top--;
    return temp;
}

/**
 * Return the top item of the stack without removing it
 * 
 * @return top item of stack
 */
template <typename T>
T Stack<T>::peek(void) {
    return list[top];
}

/**
 * Returns the number of elements on the stack
 * 
 * @return number of element on stack
 */
template <typename T>
int Stack<T>::getSize(void) {
    return top;
}

/**
 * Returns true if the stack has 0 elements on it
 * 
 * @return true if zero elements are on the stack
 */
template <typename T>
bool Stack<T>::isEmpty(void) {
    return getSize() == 0;
}