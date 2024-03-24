#!/bin/bash

# Check if cmake is installed and install if not
if ! command -v cmake &> /dev/null; then
    echo "cmake could not be found. Installing cmake..."
    sudo apt install cmake -y
fi

# Check if make is installed and install if not
if ! command -v make &> /dev/null; then
    echo "make could not be found. Installing make..."
    sudo apt install make -y
fi

# Check if java is installed
if ! command -v java &> /dev/null; then
    echo "java could not be found. Installing java..."
    sudo apt install openjdk-11-jdk -y
fi

# Check if java jdk is atleast version 11 and install if not
if [ "$(java -version 2>&1 | awk -F '"' '/version/ {print $2}' | awk -F '.' '{print $1}')" -lt 11 ]; then
    echo "Java version is less than 11. Installing java 11..."
    sudo apt install openjdk-11-jdk -y
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
    alias dpli='./build/dpli'
else
    echo "Compilation failed."
fi