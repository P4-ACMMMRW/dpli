[![Build and Test](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml/badge.svg?branch=main)](https://github.com/P4-ACMMMRW/dpli/actions/workflows/build_and_test.yml)
[![Linting](https://github.com/P4-ACMMMRW/dpli/actions/workflows/linting.yml/badge.svg?branch=main)](https://github.com/P4-ACMMMRW/dpli/actions/workflows/linting.yml)

# DPL Interpreter
The official interpreter for Data Preprocessing Language (DPL). DPL is a domain-specific language for preprocessing of tabular data. DPL has a built-in `table` type to represent tabular data and has unique syntax for filtering data along with special `union` and `intersection` operators. The syntax of DPL is similar to Python since this is a language that is already popular within this domain.

## Documentation
Language documentation and program examples can be found under the `docs/` folder.

## Future Plans
- [ ] Modules
- [ ] Compound Operators
- [ ] More Str, List, Column, and Table Operations
- [ ] Dictionaries
- [ ] Smarter readTable
- [ ] Better Error Messages

## Precompiled Binaries
Precompiled binaries can be found under the actions tab on github.

## How to Compile
On Ubuntu simply run:
```bash
./scripts/compile.sh
```

On other platforms:
```
mkdir build
cd build
cmake ..; cmake --build .
```

### Dependencies
- `Java JDK 11+`
- `cmake`
- `c++17 compiler`
