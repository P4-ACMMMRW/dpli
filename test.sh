#!/bin/bash

# Check if build directory exists
if [ ! -d build ]; then
    echo "Build directory does not exist. Please compile the project first."
    exit 1
fi

# Check if cmake is installed
if ! command -v cmake &> /dev/null; then
    echo "cmake could not be found. Please install cmake and try again."
    exit 1
fi

cd build
ctest --output-on-failure