#!/bin/bash

# Check if two arguments are passed
if [ "$#" -ne 2 ]; then
    echo "Usage: ./generate_tree.sh <input-file> <output-file>"
    exit 1
fi

# Check if graphviz is installed. if not install it (sudo apt install graphviz -y)
if ! command -v dot &> /dev/null; then
    echo "graphviz could not be found. Installing graphviz..."
    sudo apt install graphviz -y
fi

# Check if dpli file in build directory exists
if [ ! -f build/dpli ]; then
    echo "dpli not found. Compiling the project..."
    chmod +x compile.sh && ./compile.sh
fi

# If tree directory does not exist, create it
if [ ! -d tree ]; then
    mkdir tree
fi

./build/dpli $1 tree/$2

# Wait for the tree to be generated and then convert it to png
dot -Tpng tree/$2 -o tree/$2.png
