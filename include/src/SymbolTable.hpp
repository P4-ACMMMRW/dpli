#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Symbol.hpp"
#include "SymbolTableEntry.hpp"

namespace dplsrc {
class SymbolTable {
   public:
    void bind(Symbol sym);
    SymbolTableEntry *lookup(const std::string &name);
    void enter();
    void exit();

   private:
    std::stack<Symbol> table;
    std::unordered_map<std::string, SymbolTableEntry> symbolLookupTable;
};
}  // namespace dplsrc

#endif