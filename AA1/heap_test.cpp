// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "heap.h"

int main() {
    Heap *heap = new Heap();

    int num_operations, num, min;
    string input_path, output_path, operation;
    
    // Get input file path
    cin >> input_path;
    // Get size of test
    cin >> num_operations;

    // Create and open output test file
    output_path = input_path;
    output_path = output_path.substr(3, 5);
    output_path = "out/" + output_path + "_heap.out";
    ofstream output_file(output_path);

    // Print test and test size
    cout << "Running " << input_path << " with " << num_operations << " elements" << endl; 
    
    // Read and execute commands from test
    while (cin) {
        cin >> operation;
        if (operation == "push") {
            cin >> num;
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

    cout << "Done! Test output stored in " << output_path << endl;

    // Close output file
    output_file.close();    

    delete heap;

    return 0;
}
