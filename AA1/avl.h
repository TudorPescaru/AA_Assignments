// Copyright 2020 Pescaru Tudor-Mihai 321CA
#ifndef __AVL_H__
#define __AVL_H__

class Node {
    public:
    int value;
    Node *left;
    Node *right;
    int height;

    Node(int value);
};

class AVL {
    public:
    Node *root = NULL;

    AVL();
    ~AVL();

    void insertValue(int value);
    void removeMinValue();
    int getMinValue();

    private:
    int max(int a, int b);
    int height(Node *node);
    int getBalance(Node *node);
    Node* getMinNode(Node *node);
    Node* rotateRight(Node *toRotate);
    Node* rotateLeft(Node *toRotate);
    Node* insertNode(Node* node, int value);
    Node* removeNode(Node* node, int value);
    Node* clearAVL(Node *node);
};

#endif  // __AVL_H__