#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Symbol.hpp"

namespace dplsrc {
class SymbolTable {
   public:
    // Rule of five
    virtual ~SymbolTable() = default;
    SymbolTable(const SymbolTable& other) = default;
    SymbolTable(SymbolTable&& other) noexcept = default;
    SymbolTable& operator=(const SymbolTable& other) = default;
    SymbolTable& operator=(SymbolTable&& other) noexcept = default;

    SymbolTable() = default;

    /**
     * Prints the state of the table to stdout
     */
    virtual void print() = 0;
};
}  // namespace dplsrc

#endif