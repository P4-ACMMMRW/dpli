#!/bin/bash

run_perf() {
    $1 record ./build/dpli docs/examples/quicksort.dpl
    $1 stat -d ./build/dpli docs/examples/quicksort.dpl
    $1 report > perf_report.txt
}

# Check if dpli exists otherwise compile
if [ ! -f ./build/dpli ]; then
    echo "dpli could not be found. Compiling dpli..."
    ./compile.sh
fi

# Check if wsl2
if grep -qEi "(Microsoft|WSL)" /proc/version &> /dev/null; then
    echo "WSL2 detected. Using perf_wsl2..."
    run_perf ./perf_wsl2
    exit 0
fi

# Check if perf is installed and install if not
if ! command -v perf &> /dev/null; then
    echo "perf could not be found. Installing perf..."
    sudo apt install linux-tools-common linux-tools-generic -y
    run_perf perf
fi
