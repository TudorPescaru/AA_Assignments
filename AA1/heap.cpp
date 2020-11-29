// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>

#include "heap.h"

using namespace std;

// Intialise an empty heap
Heap::Heap() {
    heapVector = {};
}

// Intialise a heap with a given vector that gets heapified
Heap::Heap(vector<int> v) {
    heapVector = buildHeap(v);
}

// Heapify a given vector
vector<int> Heap::buildHeap(vector<int> &v) {
    // Start from the end of the vector and calculate index of parent
    int startInd = PARENT(v.size() - 1);
    // For each element in vector, from back to front
    for (int currInd = startInd; currInd >= 0; currInd--) {
        // Perform removal fix from current index to end
        removeFix(currInd, v.size() - 1, v);
    }
    return v;
}

// Add a new value to the heap
void Heap::insertValue(int value) {
    // Add value at the end of heap vector
    heapVector.push_back(value);
    // Fix heap vector so that heap property is maintained
    insertFix(heapVector.size() - 1);
}

// Remove the minimum value of the heap
void Heap::removeMinValue() {
    // Check if heap is not empry
    if (heapVector.empty()) {
        return;
    }
    // Swap first(smallest) and last values
    swap(heapVector[0], heapVector[heapVector.size() - 1]);
    // Remove value at the end
    heapVector.pop_back();
    // Fix heap vector so that heap property is maintained
    removeFix(0, heapVector.size() - 1, heapVector);
}

// Get smallest value in the heap
int Heap::getMinValue() {
    if (heapVector.empty()) {
        return -1;
    }
    return heapVector[0];
}

// Fix heap vector upon insertion
void Heap::insertFix(int currInd) {
    int parentInd = PARENT(currInd);
    // For each node, swap with parent if parent is smaller
    while (currInd > 0 && heapVector[parentInd] > heapVector[currInd]) {
        swap(heapVector[parentInd], heapVector[currInd]);
        // Get new parent index
        currInd = parentInd;
        parentInd = PARENT(currInd);
    }
}

// Fix heap vector upon removal
void Heap::removeFix(int currInd, int endInd, vector<int> &heap) {
    int indToSwap, leftSon, rightSon;
    // Get index of left son of current element
    leftSon = LEFT_SON(currInd);
    // While we have a left son
    while (leftSon <= endInd) {
        // Get index of right son of current element
        rightSon = RIGHT_SON(currInd);
        // Check if right son exists in vector
        if (rightSon > endInd) {
            rightSon = -1;
        }
        // Get the smallest of the two sons if they both exist
        if (rightSon != -1 && heapVector[rightSon] < heapVector[leftSon]) {
            indToSwap = rightSon;
        } else {
            indToSwap = leftSon;
        }
        // If current node is smaller than the largest son swap them
        if (heap[indToSwap] < heap[currInd]) {
            swap(heap[indToSwap], heap[currInd]);
            // Move to index of left son and recalculate left son index
            currInd = indToSwap;
            leftSon = LEFT_SON(currInd);
        } else {
            return;
        }
    }
}
