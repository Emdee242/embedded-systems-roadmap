#!/bin/bash
g++ -std=c++17 -Wall -Wextra -I src/core -I test/unity test/test_circular_buffer.cpp src/core/CircularBuffer.cpp test/unity/unity.c -o test/run_tests && ./test/run_tests