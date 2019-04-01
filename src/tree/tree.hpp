#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"

template <typename T>
class Tree {
private:
    Node<T>* root;

public:
    Tree(T rootElement) { root = new Node<T>(nullptr, nullptr, nullptr, &rootElement); }

    // returns the root of the tree
    Node<T>* getRoot() { return root; }

    T setElement(Node<T>* Node, T element);

    Node<T>* setLeft(Node<T>* Node, T element);
    Node<T>* setRight(Node<T>* Node, T element);

    Node<T>* getParent(Node<T>* Node);
    Node<T>* getLeft(Node<T>* Node);
    Node<T>* getRight(Node<T>* Node);
};

#include "tree.tcc"

#endif // !TREE_HPP