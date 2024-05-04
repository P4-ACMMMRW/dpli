#!/bin/bash

# Make a temporary file to store all examples
tmpfile=$(mktemp /tmp/tmp.XXXXXXXXXX.dpl)
for file in docs/examples/*; do
    cat "$file" >> "$tmpfile"
    echo "" >> "$tmpfile"
done

# Check if valgrind is installed and install if not
if ! command -v valgrind &> /dev/null; then
    echo "valgrind could not be found. Installing valgrind..."
    sudo apt install valgrind -y
fi

# Check for memory leaks
echo "Checking for memory leaks..."
valgrind --leak-check=full --errors-for-leak-kinds=definite --error-exitcode=1 ./build/dpli "$tmpfile"