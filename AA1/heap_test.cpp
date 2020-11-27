// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "heap.h"

int main(int argc, char *argv[]) {
    Heap *heap = new Heap();

    if (argc < 2) {
        cout << "No test file provided!" << endl;
        delete heap;
        exit(-1);
    }

    ifstream input_file(argv[1]);
    string output_path = argv[1];
    output_path = output_path.substr(3, 5);
    output_path = "out/" + output_path + ".out";
    ofstream output_file(output_path);
    int num_operations, num, min;
    string operation;
    input_file >> num_operations;
    
    while (!input_file.eof()) {
        input_file >> operation;
        if (operation == "push") {
            input_file >> num;
            heap->insertValue(num);
            output_file << "Pushed value: " << num << endl;
        } else if (operation == "pop") {
            min = heap->getMinValue();
            heap->removeMinValue();
            output_file << "Popped min value: " << min << endl;
        } else if (operation == "min") {
            if (heap->getMinValue() == -1) {
                output_file << "No min value!" << endl;
            } else {
                output_file << "Get min value: " << heap->getMinValue() << endl;
            }
        }
    }

    input_file.close();
    output_file.close();    

    delete heap;

    return 0;
}