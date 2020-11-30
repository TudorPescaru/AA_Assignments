#!/usr/bin/python3
# Copyright 2020 Pescaru Tudor-Mihai 321CA
import random

# Dir with input test files
path_in = "in/"
# Dir with output test files
path_out = "out/"
# Number of values to be added to priority queue
test_sizes = [10000, 100000, 1000000]
# Operations to be performed on priority queue
operation_types = ["push", "pop", "min"]

def create_test_predefined(size, f, pop=False, decreasing=False):
    # Write test size
    f.write(str(size) + '\n')
    # Write test operations + numbers
    for i in range(size):
        # Check if test is for increasing or decreasing numbers
        if decreasing is True:
            num = size - i - 1
        else:
            num = i
        f.write(operation_types[0] + ' ' + str(num) + '\n')
        # Check if test should contain pops
        if pop is True:
            # Every push has a 50/50 chance to come alongsied a pop
            to_pop = random.randint(0, 1)
            if to_pop == 1:
                f.write(operation_types[1] + '\n')
        # Every push has a 50/50 chance to come alongside a peek
        to_min = random.randint(0, 1)
        if to_min == 1:
            f.write(operation_types[2] + '\n')

def create_test_random(size, f, pop=False):
    # Write test size
    f.write(str(size) + '\n')
    # Write test operations + numbers
    for _ in range(size):
        # Generate a random number in given interval
        num = random.randint(0, size - 1)
        f.write(operation_types[0] + ' ' + str(num) + '\n')
        # Check if test should contain pops
        if pop is True:
            # Every push has a 50/50 chance to come alongsied a pop
            to_pop = random.randint(0, 1)
            if to_pop == 1:
                f.write(operation_types[1] + '\n')
        # Every push has a 50/50 chance to come alongside a peek
        to_min = random.randint(0, 1)
        if to_min == 1:
            f.write(operation_types[2] + '\n')

# Create each test file
for i in range(10):
    file_name = "test" + str(i) + ".in"
    path = path_in + file_name
    with open(path, "w+") as f:
        f.write(path + ' ')
        if i == 0:
            create_test_predefined(test_sizes[1], f)
        elif i == 1:
            create_test_predefined(test_sizes[1], f, True)
        elif i == 2:
            create_test_predefined(test_sizes[1], f, False, True)
        elif i == 3:
            create_test_predefined(test_sizes[1], f, True, True)
        elif i == 4:
            create_test_random(test_sizes[0], f)
        elif i == 5:
            create_test_random(test_sizes[0], f, True)
        elif i == 6:
            create_test_random(test_sizes[1], f)
        elif i == 7:
            create_test_random(test_sizes[1], f, True)
        elif i == 8:
            create_test_random(test_sizes[2], f)
        elif i == 9:
            create_test_random(test_sizes[2], f, True)

        
