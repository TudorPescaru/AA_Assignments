// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <vector>

using namespace std;

#include "avl.h"

int main() {
    AVL *avl = new AVL();
    vector<int> v = {1, 9, 2, 8, 3, 7, 4, 6, 5};
    int min;
    for (int i = 0; i < v.size(); ++i) {
        avl->insertValue(v[i]);
    }
    
    while (avl->root != NULL) {
        min = avl->getMinValue();
        avl->removeMinValue();
    }

    delete avl;

    return 0;
}