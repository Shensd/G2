#ifndef TREE_HPP
#define TREE_HPP

#include "position.hpp"

#include <iostream>

template <typename T>
class Tree {
protected:

    /**
     * Protected node class is used to hide functions from user
     */
    template <typename E>
    class Node : public Position<E>{
    private:
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;

        E* element;
    public:
        Node(Node* parent, Node* left, Node* right, E* element) : 
            parent(parent), 
            left(left), 
            right(right), 
            element(element) {}

        E* getElement() { return element; }
        Node* getParent() { return parent; }
        Node* getLeft() { return left; }
        Node* getRight() { return right; }

        void setElement(E* element) { Node::element = element; }
        void setParent(Node* parent) { Node::parent = parent; }
        void setLeft(Node* left) { Node::left = left; }
        void setRight(Node* right) { Node::right = right; }
    };
    
private:
    Node<T>* root;

    Node<T>* validatePosition(Position<T>* position);

public:
    Tree(T rootElement) { root = new Node<T>(nullptr, nullptr, nullptr, &rootElement); }

    // returns the root of the tree
    Position<T>* getRoot() { return root; }

    T setElement(Position<T>* position, T* element);

    Position<T>* setLeft(Position<T>* position, T* element);
    Position<T>* setRight(Position<T>* position, T* element);

    Position<T>* getParent(Position<T>* position);
    Position<T>* getLeft(Position<T>* position);
    Position<T>* getRight(Position<T>* position);
};

#include "tree.tcc"

#endif // !TREE_HPP