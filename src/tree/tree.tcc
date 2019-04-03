#ifndef TREE_TCC
#define TREE_TCC

/**
 * Converts a Position object into a Node object
 * 
 * @param position position to convert
 * @returns node equivalent
 */
template<typename T>
Tree<T>::Node<T>* Tree<T>::validatePosition(Position<T>* position) {
    return (Node<T>*) position;
}

/**
 * Set the element at a given position
 * 
 * @param position position to set element of
 * @param element element to set to
 * @returns element previously stored at position
 */
template<typename T>
T Tree<T>::setElement(Position<T>* position, T element) {
    Node<T>* node = validatePosition(position);

    T old = *node->getElement();

    node->setElement(element);

    return old;
}

/**
 * Set the left element of a given position
 * 
 * @param position position to set left of
 * @param element element to set left to
 * @returns position of new node
 */
template <typename T> 
Position<T>* Tree<T>::setLeft(Position<T>* position, T element) {
    Node<T>* parent = validatePosition(position);

    Node<T>* left = new Node<T>(parent, nullptr, nullptr, element);
   
    parent->setLeft(left);

    return left;
}

/**
 * Set the root to a new position
 * 
 * @param position new position to set root to
 */
template <typename T>
void Tree<T>::setRoot(Position<T>* position) {
    Tree<T>::root = validatePosition(position);
}

/**
 * Set the left element of a given position to the root of a given tree
 * 
 * @param position position to replace with tree
 * @param tree tree to replace with 
 */
template <typename T>
void Tree<T>::setLeftTree(Position<T>* position, Tree<T>* tree) {
    Node<T>* parent = validatePosition(position);

    parent->setLeft(
        (Node<T>*)tree->getRoot()
    );

    tree->setRoot(Tree<T>::getRoot());
}

/**
 * Set the right element of a given position to the root of a given tree
 * 
 * @param position position to replace with tree
 * @param tree tree to replace with 
 */
template <typename T>
void Tree<T>::setRightTree(Position<T>* position, Tree<T>* tree) {
    Node<T>* parent = validatePosition(position);

    parent->setRight(
        (Node<T>*)tree->getRoot()
    );

    tree->setRoot(Tree<T>::getRoot());
}

/**
 * Set the right element of a given position
 * 
 * @param position position to set right of
 * @param element element to set right to
 * @returns position of new node
 */
template <typename T>
Position<T>* Tree<T>::setRight(Position<T>* position, T element) {
    Node<T>* parent = validatePosition(position);

    Node<T>* right = new Node<T>(parent, nullptr, nullptr, element);
    
    parent->setRight(right);

    return right;
}

/**
 * Get the parent of a given position
 * 
 * @param position position to get parent of
 * @returns parent of position
 */
template <typename T>
Position<T>* Tree<T>::getParent(Position<T>* position) {
    Node<T>* node = validatePosition(position);

    return node->getParent();
}

/**
 * Get the left child of a given position
 * 
 * @param position position to get left child of
 * @returns left child of position
 */
template <typename T>
Position<T>* Tree<T>::getLeft(Position<T>* position) {
    Node<T>* node = validatePosition(position);

    return node->getLeft();
}

/**
 * Get the right child of a given position
 * 
 * @param position position to get right child of
 * @returns right child of position
 */
template <typename T>
Position<T>* Tree<T>::getRight(Position<T>* position) {
    Node<T>* node = validatePosition(position);

    return node->getRight();
}

#endif // !TREE_TCC