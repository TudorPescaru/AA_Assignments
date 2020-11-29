// Copyright 2020 Pescaru Tudor-Mihai 321CA
#ifndef __AVL_H__
#define __AVL_H__

class Node {
    public:
    int value;
    Node *left;
    Node *right;
    int height;
    
    // Constructor that creates node with given value
    Node(int value);
};

class AVL {
    public:
    Node *root;

    // Contructor that initialises root  
    AVL();
    // Destructor that clears all nodes in AVL
    ~AVL();

    // Insert a value into AVL
    void insertValue(int value);
    // Remove the minimum value from AVL
    void removeMinValue();
    // Get minimum value in AVL
    int getMinValue();

    private:
    // Return maximum of two nodes
    int max(int a, int b);
    // Return height of node
    int height(Node *node);
    // Return balance factor of a node
    int getBalance(Node *node);
    // Get node with minimum value in AVL
    Node* getMinNode(Node *node);
    // Perform right rotation on a node
    Node* rotateRight(Node *toRotate);
    // Perform left rotation on a node
    Node* rotateLeft(Node *toRotate);
    // Insert a node with a given value
    Node* insertNode(Node* node, int value);
    // Remove node that contains given value
    Node* removeNode(Node* node, int value);
    // Clear all nodes in the AVL
    Node* clearAVL(Node *node);
};

#endif  // __AVL_H__
