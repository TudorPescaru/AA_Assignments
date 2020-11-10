// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>

using namespace std;

#include "heap.h"

Heap::Heap() {
    heapVector = {};
}

Heap::Heap(vector<int> v) {
    heapVector = buildHeap(v);
}

vector<int> Heap::buildHeap(vector<int> &v) {
    int startInd = PARENT(v.size() - 1);
    for (int currInd = startInd; currInd >= 0; currInd--) {
        removeFix(currInd, v.size() - 1, v);
    }
    return v;
}

void Heap::insertValue(int value) {
    heapVector.push_back(value);
    insertFix(heapVector.size() - 1);
}

void Heap::removeMinValue() {
    swap(heapVector[0], heapVector[heapVector.size() - 1]);
    heapVector.pop_back();
    removeFix(0, heapVector.size() - 1, heapVector);
}

int Heap::getMinValue() {
    return heapVector[0];
}

void Heap::insertFix(int currInd) {
    int parentInd = PARENT(currInd);
    while (currInd > 0 && heapVector[parentInd] > heapVector[currInd]) {
        swap(heapVector[parentInd], heapVector[currInd]);
        currInd = parentInd;
        parentInd = PARENT(currInd);
    }
}

void Heap::removeFix(int currInd, int endInd, vector<int> &v) {
    int indToSwap, leftSon, rightSon;
    leftSon = LEFT_SON(currInd);
    while (leftSon <= endInd) {
        rightSon = RIGHT_SON(currInd);
        if (rightSon > endInd) {
            rightSon = -1;
        }
        if (rightSon != -1 && heapVector[rightSon] < heapVector[leftSon]) {
            indToSwap = rightSon;
        } else {
            indToSwap = leftSon;
        }
        if (heapVector[indToSwap] < heapVector[currInd]) {
            swap(heapVector[indToSwap], heapVector[currInd]);
            currInd = indToSwap;
            leftSon = LEFT_SON(currInd);
        } else {
            return;
        }
    }
}
