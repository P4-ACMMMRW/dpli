[![Build and Test](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml)

# DPL
## Build
### Linux
```bash
chmod +x compile.sh && ./compile.sh
```
Then use
```bash
cd build

./dpli <file>
```
to run the dpl interpreter

#### Generate Parse Tree PNG
(OPS need to install graphvis)

```bash
sudo apt-get install graphviz
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
