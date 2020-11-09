// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <bits/stdc++.h>

using namespace std;

#include "avl.h"

Node::Node(int value) {
    value = value;
    left = NULL;
    right = NULL;
    height = 1;
}

AVL::AVL(int value) {
    root = new Node(value);
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

Node* AVL::getMinValue(Node *node) {
    Node *curr = node;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

Node* AVL::rightRotate(Node *toRotate) {
    Node *newRoot = toRotate->left;
    Node *tmp = newRoot->right;

    newRoot->right = toRotate;
    toRotate->left = tmp;

    toRotate->height = max(height(toRotate->left), height(toRotate->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

Node* AVL::leftRotate(Node *toRotate) {
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
        node = new Node(value);
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
        return rightRotate(node);
    }

    if (balance < -1 && value > node->right->value) {
        return leftRotate(node);
    }

    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* AVL::deleteNode(Node* node, int value) {
    if (node == NULL) {
        return node;
    }

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    } else {
        if (node->left == NULL || node->right == NULL) {
            Node *tmp = node->left ? node->left : node->right;

            if (tmp == NULL) {
                tmp = node;
                node = NULL;
            } else {
                *node = *tmp;
                free(tmp);
            }
        } else {
            Node *tmp = getMinValue(node->right);
            node->value = tmp->value;
            node->right = deleteNode(node->right, tmp->value);
        }
    }

    if (node == NULL) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node->left);
    }

    return node;
}

