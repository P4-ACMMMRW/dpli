#!/bin/bash

run_perf() {
    # Make a temporary file to store all examples
    tmpfile=$(mktemp /tmp/tmp.XXXXXXXXXX.dpl)
    for file in docs/examples/*; do
        cat "$file" >> "$tmpfile"
        echo "" >> "$tmpfile"
    done

    # Benchmark interpreter
    $1 record ./build/dpli "$tmpfile"
    $1 report > perf_report.txt
    echo "Generating stats..."
    $1 stat -r 10 -e cache-misses,cycles,instructions,context-switches,cpu-migrations,faults,branches,branch-misses ./build/dpli "$tmpfile" >> perf_report.txt
    #rm "$tmpfile"
}

# Check if dpli exists otherwise compile
if [ ! -f ./build/dpli ]; then
    echo "dpli could not be found. Compiling dpli..."
    ./compile.sh
fi

# Check if wsl2
if grep -qEi "(Microsoft|WSL)" /proc/version &> /dev/null; then
    echo "WSL2 detected. Using perf_wsl2..."
    run_perf ./lib/perf/perf_wsl2
    exit 0
fi

# Check if perf is installed and install if not
if ! command -v perf &> /dev/null; then
    echo "perf could not be found. Installing perf..."
    sudo apt install linux-tools-common linux-tools-generic -y
    run_perf perf
fi
