#!/bin/bash

# Check if clang-format is installed. If not install it
if ! command -v clang-format &> /dev/null; then
    echo "clang-format could not be found. Installing clang-format..."
    sudo apt install clang-format -y
fi

# Check if clang-tidy is installed. If not install it
if ! command -v clang-tidy &> /dev/null; then
    echo "clang-tidy could not be found. Installing clang-tidy..."
    sudo apt install clang-tidy -y
fi

# If build/compile_commands.json does not exist, then run ./compile.sh to generate it
if [ ! -f "build/compile_commands.json" ]; then
    echo "compile_commands.json not found. Running: ./compile.sh to generate it..."
    ./scripts/compile.sh
fi

# Run clang-format and clang-tidy on all cpp and hpp files in the project except in lib and build directories
for file in $(find . -name '*.cpp' -o -name '*.hpp' | grep -v -e '^./lib/' -e '^./build/' -e '^./tests/'); do
    echo "Running clang-format on: $file"
    clang-format -i $file

    # If arg format-only skip clang-tidy
    if [ "$1" == "format-only" ]; then
        echo ""
        continue
    fi
    
    echo "Running clang-tidy on: $file"
    clang-tidy -p build -checks='boost-*,bugprone-*,performance-*,readability-*,portability-*,clang-analyzer-*,cppcoreguidelines-*' -fix -extra-arg=-std=c++17 $file
    echo ""
done