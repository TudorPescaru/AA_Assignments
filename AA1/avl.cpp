// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>

using namespace std;

#include "avl.h"

// Create a new node with given value
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

// Insert a value by inserting a new node with given value
void AVL::insertValue(int value) {
    this->root = this->insertNode(this->root, value);
}

// Remove minimum value by removing the node that contains the minimum value
void AVL::removeMinValue() {
    if (this->getMinValue() == -1) {
        return;
    }
    this->root = this->removeNode(this->root, this->getMinValue());
}

// Get the minimum value by finding the node that contains the minimum value
int AVL::getMinValue() {
    if (this->root != NULL) {
        return this->getMinNode(this->root)->value;
    }
    return -1;
}

// Get the maximum of two values
int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

// Get the height of a node
int AVL::height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Get the balance factor of a node
int AVL::getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Get leftmost node in AVL
Node* AVL::getMinNode(Node *node) {
    Node *curr = node;
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

// Perform right totation on a node
Node* AVL::rotateRight(Node *toRotate) {
    // Get the new root and third extra node to be rotated
    Node *newRoot = toRotate->left;
    Node *tmp = newRoot->right;

    // Perform rotation
    newRoot->right = toRotate;
    toRotate->left = tmp;

    // Recalculate heights
    toRotate->height = max(height(toRotate->left), height(toRotate->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// Perform left rotation on a node
Node* AVL::rotateLeft(Node *toRotate) {
    // Get the new root and third extra node to be rotated
    Node *newRoot = toRotate->right;
    Node *tmp = newRoot->left;

    // Perform rotation
    newRoot->left = toRotate;
    toRotate->right = tmp;

    // Recalculate heights
    toRotate->height = max(height(toRotate->left), height(toRotate->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

// Insert a node with given value
Node* AVL::insertNode(Node* node, int value) {
    // If a null position has been reached add new node with value
    if (node == NULL) {
        return new Node(value);
    }

    // Check if the value to be inserted is greater or smaller than current value
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    } else {
        // The same value cannot be inserted twice
        return node;
    }

    // Set the height of the inserted node
    node->height = max(height(node->left), height(node->right)) + 1;

    // Get the balance factor of the inserted node
    int balance = getBalance(node);

    // Fix AVL tree based on balance
    // Left Left Case
    if (balance > 1 && value < node->left->value) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && value > node->right->value) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left Case
    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Remove node with given value
Node* AVL::removeNode(Node* node, int value) {
    // If postion is null return
    if (node == NULL) {
        return node;
    }
    
    // Check if value to be removed is greater or smaller than current value
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        // Check if node with value has only one child
        if (node->left == NULL || node->right == NULL) {
            Node *tmp = node->left ? node->left : node->right;
            // If there are no children delete and set it as null
            if (tmp == NULL) {  
                tmp = node;  
                node = NULL;  
            } else {
                // Swap node with non null children
                node->value = tmp->value;
                node->left = tmp->left;
                node->right = tmp->right;
                node->height = tmp->height;
            }
            delete tmp;
        } else {
            // If node has both children get inorder successor
            Node *tmp = getMinNode(node->right);
            // Assign value of inorder successor to current node
            node->value = tmp->value;
            // Delete inorder succesor
            node->right = removeNode(node->right, tmp->value);
        }
    }
    
    // Check if node has been deleted
    if (node == NULL) {
        return node;
    }

    // Reset height of current node
    node->height = max(height(node->left), height(node->right)) + 1;
    
    // Get balance factor of node
    int balance = getBalance(node);

    // Fix AVL based on balance factor
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Clear all nodes in AVL
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

