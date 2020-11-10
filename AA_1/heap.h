// Copyright 2020 Pescaru Tudor-Mihai 321CA
#ifndef __HEAP_H__
#define __HEAP_H__

#include <vector>

#define PARENT(i)     (((i) - 1) >> 1)
#define LEFT_SON(i)   (((i) << 1) + 1)
#define RIGHT_SON(i)  (((i) << 1) + 2)

class Heap {
    public:
    vector<int> heapVector;

    Heap();
    Heap(vector<int> v);

    void insertValue(int value);
    void removeMinValue();
    int getMinValue();

    private:
    vector<int> buildHeap(vector<int> &v);
    void insertFix(int currInd);
    void removeFix(int currInd, int endInd, vector<int> &v);
};

#endif // __HEAP_H__