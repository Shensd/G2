#ifndef TREE_HPP
#define TREE_HPP

template <class T>
class Tree {
private:

    class Node {
        Node* left;
        Node* right;
        Node* parent;
        T value;

        Node(Node* left, Node* right, Node* parent, T value) :
            left(left), right(right), parent(parent), value(value) {}
    };

    Node root;
    
    bool rootSet = false;
public:
    Tree();

    Node getParent(Node n) { return n.parent; }

    void setRoot(T value);
    Node getRoot() { return root; }

    T getValue(Node n);
};

#include "tree.tcc"

#endif // !TREE_HPP