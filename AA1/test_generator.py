#!/usr/bin/python3
# Copyright 2020 Pescaru Tudor-Mihai 321CA
import random

path_in = "in/"
path_out = "out/"
test_sizes = [10000, 100000, 1000000]
operation_types = ["push", "pop", "min"]

def create_test_predefined(size, f, pop=False, decreasing=False):
    f.write(str(size) + '\n')
    for i in range(size):
        if decreasing is True:
            num = size - i - 1
        else:
            num = i
        f.write(operation_types[0] + ' ' + str(num) + '\n')
        if pop is True:
            to_pop = random.randint(0, 1)
            if to_pop == 1:
                f.write(operation_types[1] + '\n')
        to_min = random.randint(0, 1)
        if to_min == 1:
            f.write(operation_types[2] + '\n')

def create_test_random(size, f, pop=False):
    f.write(str(size) + '\n')
    for _ in range(size):
        num = random.randint(0, size - 1)
        f.write(operation_types[0] + ' ' + str(num) + '\n')
        if pop is True:
            to_pop = random.randint(0, 1)
            if to_pop == 1:
                f.write(operation_types[1] + '\n')
        to_min = random.randint(0, 1)
        if to_min == 1:
            f.write(operation_types[2] + '\n')

for i in range(10):
    file_name = "test" + str(i) + ".in"
    path = path_in + file_name
    with open(path, "w+") as f:
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

        