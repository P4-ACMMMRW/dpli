#!/bin/bash

# Check if cmake is installed
if ! command -v cmake &> /dev/null; then
    echo "cmake could not be found. Please install cmake and try again."
    exit 1
fi

# Check if make is installed
if ! command -v make &> /dev/null; then
    echo "make could not be found. Please install make and try again."
    exit 1
fi

# If ./build clean
if [ "$1" == "clean" ]; then
    rm -rf build
fi

# Check if build directory exists
if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make

# Wait until done compiling and then run tests
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running tests..."
    ctest --output-on-failure
else
    echo "Compilation failed."
fi