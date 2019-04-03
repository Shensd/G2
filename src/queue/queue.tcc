template <typename T>
Queue<T>::Queue(int maxSize) : maxSize(maxSize) {
    list = std::vector<T>(size);
}

template <typename T>
Queue<T>::Queue() {
    Queue::Queue(DEFAULT_CAPACITY);
}

/**
 * Add an item to the back of the queue
 * 
 * @element item to add to queue
 */
template <typename T>
void Queue<T>::enqueue(T element) {
    list[(front + size) % maxSize] = element;
    size++;
}

/**
 * Get the element at the front of the queue and remove it
 * 
 * @return element at front of queue
 */
template <typename T>
T Queue<T>::dequeue(void) {
    T temp = list[front];

    list[front] = NULL;

    front = (front + 1) % maxSize;
    size--;

    return temp;
}

/**
 * Get the element at the front of the queue without removing it
 * 
 * @return element at front of queue
 */
template <typename T>
T Queue<T>::getTop(void) {
    return list[(front + size) % maxSize];
}

/**
 * Get the number of element currently in the queue
 * 
 * @return number of elements in queue
 */
template <typename T>
int Queue<T>::getSize(void) {
    return size == 0;
}

/**
 * Returns true if the queue has 0 elements in it
 * 
 * @return true if empty
 */
template <typename T>
bool Queue<T>::isEmpty(void) {
    return getSize() == 0;
}