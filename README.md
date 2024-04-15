[![Build and Test](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml/badge.svg)](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml)

# DPL
## Build
### Ubuntu
Run the ```compile.sh``` script with:
```bash
./compile.sh
```
this will create an executable which can be run with:
```bash
cd build
./dpli <file>
```

#### Clean Build
To make a clean build run the ```compile.sh``` script with the argument "clean":
```bash
./compile.sh clean
```

#### Run Tests
After compiling the interpreter tests can be run using the ```run_tests.sh``` script:
```bash
./run_tests.sh
```

## Linting
Linting can be done with
```bash
./linter.sh
```
or
```bash
./linter format-only
```
to skip clang-tidy checks.

## Benchmarking
Benchmarking can be done with ./bench.sh
