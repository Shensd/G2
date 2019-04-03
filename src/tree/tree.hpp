#ifndef TREE_HPP
#define TREE_HPP

#include "position.hpp"

template <typename T>
class Tree {
protected:

    template <typename E>
    class Node : public Position<E>{
    private:
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;

        E element;
    public:
        Node(Node* parent, Node* left, Node* right, E element) : 
            parent(parent), 
            left(left), 
            right(right), 
            element(element) {}

        E getElement(void) { return element; }
        Node* getParent(void) { return parent; }
        Node* getLeft(void) { return left; }
        Node* getRight(void) { return right; }

        void setElement(E element) { Node::element = element; }
        void setParent(Node* parent) { Node::parent = parent; }
        void setLeft(Node* left) { Node::left = left; }
        void setRight(Node* right) { Node::right = right; }
    };
    
private:
    Node<T>* root;

    Node<T>* validatePosition(Position<T>* position);

public:
    Tree(T rootElement) { root = new Node<T>(nullptr, nullptr, nullptr, rootElement); }

    Position<T>* getRoot() { return root; }

    T setElement(Position<T>* position, T element);

    Position<T>* setLeft(Position<T>* position, T element);
    Position<T>* setRight(Position<T>* position, T element);
    
    void setRoot(Position<T>* position);
    
    void setLeftTree(Position<T>* position, Tree<T>* tree);
    void setRightTree(Position<T>* position, Tree<T>* tree);

    Position<T>* getParent(Position<T>* position);
    Position<T>* getLeft(Position<T>* position);
    Position<T>* getRight(Position<T>* position);
};

#include "tree.tcc"

#endif // !TREE_HPP