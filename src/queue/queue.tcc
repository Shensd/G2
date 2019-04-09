template <typename T>
Queue<T>::Queue(int maxSize) : maxSize(maxSize) {
    list = std::vector<T>(maxSize);
    list.reserve(maxSize);
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
    if(getSize() == maxSize) throw new std::runtime_error("Attempted to enqueue element but queue is full.");

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
    if(isEmpty()) throw new std::runtime_error("Attempted to dequeue but queue is empty");

    T temp = list[front];

    list[front] = 0;

    front = (front + 1) % maxSize;
    size--;

    return temp;
}

/**
 * Get the element at the front of the queue without removing it
 * 
 * @return element at front of queue, or nullptr if empty
 */
template <typename T>
T Queue<T>::getTop(void) {
    if(isEmpty()) return nullptr;

    return list[(front + size) % maxSize];
}

/**
 * Get the number of element currently in the queue
 * 
 * @return number of elements in queue
 */
template <typename T>
int Queue<T>::getSize(void) {
    return size;
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