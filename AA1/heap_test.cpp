// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <fstream>
#include <string>

#include "heap.h"

using namespace std;

int main(int argc, char *argv[]) {
    Heap *heap = new Heap();

    // Check if program has an input test file arg
    if (argc < 2) {
        cout << "No test file provided!" << endl;
        delete heap;
        exit(-1);
    }

    // Open input test file
    ifstream input_file(argv[1]);
    
    // Create and open output test file
    string output_path = argv[1];
    output_path = output_path.substr(3, 5);
    output_path = "out/" + output_path + ".out";
    ofstream output_file(output_path);
    
    int num_operations, num, min;
    string operation;
    
    // Get size of test 
    input_file >> num_operations;

    // Print test and test size
    cout << "Running " << argv[1] << " with " << num_operations << " elements" << endl; 
    
    // Read and execute commands from test
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

    // Close files
    input_file.close();
    output_file.close();    

    delete heap;

    return 0;
}
