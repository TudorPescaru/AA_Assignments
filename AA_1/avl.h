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

    AVL(int value);

    int max(int a, int b);
    int height(Node *node);
    int getBalance(Node *node);
    Node* getMinValue(Node *node);
    Node* rightRotate(Node *toRotate);
    Node* leftRotate(Node *toRotate);
    Node* insertNode(Node* node, int value);
    Node* deleteNode(Node* node, int value);
};

#endif  // __AVL_H__