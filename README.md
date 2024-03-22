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

#### Run Tests
After compiling the interpreter tests can be run with:

First time 
```bash
chmod +x test.sh
```
then
```bash
./test.sh
```
to verify tests.

#### Generate Parse Tree PNG
(OPS need to install graphvis)

```bash
sudo apt install graphviz -y
```

```bash
./dpli <input/file> <output/file> 
dot -Tpng output/tree.dot -o output/tree.png
```

#### Clean Build
To make a clean build run the following command:
```bash
./compile.sh clean
```
