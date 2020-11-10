// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <vector>

using namespace std;

#include "heap.h"

int main() {
    vector<int> v = {1, 9, 2, 8, 3, 7, 4, 6, 5};
    Heap *heap = new Heap();
    int min;

    for (int i = 0; i < v.size(); ++i) {
        heap->insertValue(v[i]);
    }
    
    while (!heap->heapVector.empty()) {
        min = heap->getMinValue();
        heap->removeMinValue();
    }

    delete heap;

    return 0;
}