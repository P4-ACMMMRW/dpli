#!/bin/bash

# Check if cmake is installed and install if not
if ! command -v cmake &> /dev/null; then
    echo "cmake could not be found. Installing cmake..."
    sudo apt install cmake -y
fi

# Check if dpli file in build directory exists
if [ ! -f build/dpli ]; then
    echo "dpli not found. Compiling the project..."
    chmod +x compile.sh && ./compile.sh
fi

./build/tests/unit_tests 