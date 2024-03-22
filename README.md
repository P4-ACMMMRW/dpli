[![Build and Test](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml)

# DPL
## Build
### Linux
First time do
```bash
chmod +x compile.sh
```
then 
```bash
./compile.sh
```

and lastly
```bash
cd build
./dpli <file>
```
to run the dpl interpreter

#### Clean Build
To make a clean build run the following command:
```bash
./compile.sh clean
```

#### Run Tests
After compiling the interpreter tests can be run with:

First time 
```bash
chmod +x run_tests.sh
```
then
```bash
./run_tests.sh
```
to verify tests.

#### Generate Parse Tree PNG
```bash
chmod +x generate_tree.sh
```
then
```bash
./generate_tree.sh <input-file> <output-name>
```
