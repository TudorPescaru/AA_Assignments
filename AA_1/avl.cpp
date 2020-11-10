// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>

using namespace std;

#include "avl.h"

Node::Node(int value) {
    this->value = value;
    this->left = NULL;
    this->right = NULL;
    this->height = 1;
}

AVL::AVL() {
    this->root = NULL;
}

AVL::~AVL() {
    clearAVL(this->root);
}

void AVL::insertValue(int value) {
    this->root = this->insertNode(this->root, value);
}

void AVL::removeMinValue() {
    this->root = this->removeNode(this->root, this->getMinValue());
}

int AVL::getMinValue() {
    if (this->root != NULL) {
        return this->getMinNode(this->root)->value;
    }
    return -1;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int AVL::getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node* AVL::getMinNode(Node *node) {
    Node *curr = node;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

Node* AVL::rotateRight(Node *toRotate) {
    Node *newRoot = toRotate->left;
    Node *tmp = newRoot->right;

    newRoot->right = toRotate;
    toRotate->left = tmp;

    toRotate->height = max(height(toRotate->left), height(toRotate->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

Node* AVL::rotateLeft(Node *toRotate) {
    Node *newRoot = toRotate->right;
    Node *tmp = newRoot->left;

    newRoot->left = toRotate;
    toRotate->right = tmp;

    toRotate->height = max(height(toRotate->left), height(toRotate->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

Node* AVL::insertNode(Node* node, int value) {
    if (node == NULL) {
        return new Node(value);
    }

    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    } else {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && value < node->left->value) {
        return rotateRight(node);
    }

    if (balance < -1 && value > node->right->value) {
        return rotateLeft(node);
    }

    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AVL::removeNode(Node* node, int value) {
    if (node == NULL) {
        return node;
    }
    
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        if (node->left == NULL || node->right == NULL) {
            Node *tmp = node->left ? node->left : node->right;
            if (tmp == NULL) {  
                tmp = node;  
                node = NULL;  
            } else {
                node->value = tmp->value;
                node->left = tmp->left;
                node->right = tmp->right;
                node->height = tmp->height;
            }
            delete tmp;
        } else {
            Node *tmp = getMinNode(node->right);
            node->value = tmp->value;
            node->right = removeNode(node->right, tmp->value);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node->left);
    }

    return node;
}

Node* AVL::clearAVL(Node *node) {
    if (node == NULL) {
        return node;
    }
    if (node->left != NULL) {
        node->left = clearAVL(node->left);
    }
    if (node->right != NULL) {
        node->right = clearAVL(node->right);
    }
    Node *tmp = node;
    if (node->left == NULL && node->right == NULL) {
        delete tmp;
        node = NULL;
    }
    return node;
}

