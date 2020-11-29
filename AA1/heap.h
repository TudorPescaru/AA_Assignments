// Copyright 2020 Pescaru Tudor-Mihai 321CA
#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>

// Shortcut for index of parent
#define PARENT(i)     (((i) - 1) >> 1)
// Shortcut for index of left son
#define LEFT_SON(i)   (((i) << 1) + 1)
// Shortcut for index of right son
#define RIGHT_SON(i)  (((i) << 1) + 2)

class Heap {
    public:
    vector<int> heapVector;
    
    // Constructor that initialises an empty heap
    Heap();
    // Constructor that takes a vector and turns it into a heap
    Heap(vector<int> v);

    // Insert a value into heap
    void insertValue(int value);
    // Remove the minimum value in the heap
    void removeMinValue();
    // Get the minimum value 
    int getMinValue();

    private:
    // Heapify a vector
    vector<int> buildHeap(vector<int> &v);
    // Fix heap property on insert
    void insertFix(int currInd);
    // Fix heap property on removal
    void removeFix(int currInd, int endInd, vector<int> &v);
};

#endif // __HEAP_H__
