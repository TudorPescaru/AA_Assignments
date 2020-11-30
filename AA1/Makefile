# Copyright 2020 Pescaru Tudor-Mihai 321CA
CC = g++
CFLAGS = -Wall -Wextra -Werror -g

HEAP_TARGET = heap
AVL_TARGET = avl
HEAP_OBJECTS = heap_test.o heap.o
AVL_OBJECTS = avl_test.o avl.o
HEAP_SOURCES = heap_test.cpp heap.cpp
AVL_SOURCES = avl_test.cpp avl.cpp
TEST_DIR = in/

build: $(HEAP_TARGET) $(AVL_TARGET)

$(HEAP_TARGET): $(HEAP_OBJECTS)
		$(CC) $(CFLAGS) -o $(HEAP_TARGET) $(HEAP_OBJECTS)

$(HEAP_OBJECTS):
		$(CC) $(CFLAGS) -c $(HEAP_SOURCES)

$(AVL_TARGET): $(AVL_OBJECTS)
		$(CC) $(CFLAGS) -o $(AVL_TARGET) $(AVL_OBJECTS)

$(AVL_OBJECTS):
		$(CC) $(CFLAGS) -c $(AVL_SOURCES)

clean:
		rm $(HEAP_TARGET) $(AVL_TARGET) $(HEAP_OBJECTS) $(AVL_OBJECTS)

run_tests:
		./$(HEAP_TARGET) < in/test0.in
		./$(HEAP_TARGET) < in/test1.in
		./$(HEAP_TARGET) < in/test2.in
		./$(HEAP_TARGET) < in/test3.in
		./$(HEAP_TARGET) < in/test4.in
		./$(HEAP_TARGET) < in/test5.in
		./$(HEAP_TARGET) < in/test6.in
		./$(HEAP_TARGET) < in/test7.in
		./$(HEAP_TARGET) < in/test8.in
		./$(HEAP_TARGET) < in/test9.in
		./$(AVL_TARGET) < in/test0.in
		./$(AVL_TARGET) < in/test1.in
		./$(AVL_TARGET) < in/test2.in
		./$(AVL_TARGET) < in/test3.in
		./$(AVL_TARGET) < in/test4.in
		./$(AVL_TARGET) < in/test5.in
		./$(AVL_TARGET) < in/test6.in
		./$(AVL_TARGET) < in/test7.in
		./$(AVL_TARGET) < in/test8.in
		./$(AVL_TARGET) < in/test9.in
