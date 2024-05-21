#!/bin/bash

./scripts/compile.sh

if ! command -v lcov &> /dev/null; then
    echo "lcov could not be found. Installing lcov..."
    sudo apt install lcov -y
fi

# Generate test coverage
lcov -i -c -d . --output-file base.info 2>/dev/null
lcov -c -d . --output-file test.info 2>/dev/null
lcov -a base.info -a test.info -o coverage.info
lcov --remove coverage.info '*/main/**' '*/build/**' '*/_deps/**' '/usr/*' '*/antlr4_runtime/**' '*/tests/**' '*/lib/**' --output-file coverage.info 2>/dev/null
genhtml coverage.info --output-directory coverage