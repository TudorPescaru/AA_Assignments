// Copyright 2020 Pescaru Tudor-Mihai 321CA
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sys/resource.h>

using namespace std;

#include "avl.h"

int main() {
    AVL *avl = new AVL();

    int num_operations, num, min;
    string input_path, output_path, operation;
    
    // Get input file path
    cin >> input_path;
    // Get size of test
    cin >> num_operations;

    // Create and open output test file
    output_path = input_path;
    output_path = output_path.substr(3, 5);
    output_path = "out/" + output_path + "_avl.out";
    ofstream output_file(output_path);

    // Print test and test size
    cout << "Running " << input_path  << " with " << num_operations << " elements" << endl; 
    
    auto start = chrono::high_resolution_clock::now();
    // Read and execute commands from test
    while (cin) {
        cin >> operation;
        if (operation == "push") {
            cin >> num;
            avl->insertValue(num);
            output_file << "Pushed value: " << num << endl;
        } else if (operation == "pop") {
            min = avl->getMinValue();
            avl->removeMinValue();
            output_file << "Popped min value: " << min << endl;
        } else if (operation == "min") {
            if (avl->getMinValue() == -1) {
                output_file << "No min value!" << endl;
            } else {
                output_file << "Get min value: " << avl->getMinValue() << endl;
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Done! Test output stored in " << output_path << endl;
    cout << "Total running time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    cout << "Total memory used: " << r_usage.ru_maxrss << " kilobytes" << endl;

    // Close output file
    output_file.close();

    delete avl;

    return 0;
}
