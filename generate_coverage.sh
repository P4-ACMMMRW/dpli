#!/bin/bash

# Check if dpli file in build directory exists
if [ ! -f build/dpli ]; then
    echo "dpli not found. Compiling the project..."
    ./compile.sh
fi

if ! command -v lcov &> /dev/null; then
    echo "lcov could not be found. Installing lcov..."
    sudo apt install lcov -y
fi

# Generate test coverage
lcov -i -c -d . --output-file base.info 2>/dev/null
lcov -c -d . --output-file test.info 2>/dev/null
lcov -a base.info -a test.info -o coverage.info
lcov --remove coverage.info '*/_deps/**' '/usr/*' '*/antlr4_runtime/**' '*/tests/**' '*/lib/**' --output-file coverage.info 2>/dev/null
genhtml coverage.info --output-directory coverage