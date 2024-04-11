#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Symbol.hpp"

namespace dplsrc {
class SymbolTable {
   public:
    void bind(Symbol sym);
    Symbol lookup(const Symbol& sym);
    void enter();
    void exit();

   private:
    std::stack<Symbol> table;
    std::unordered_map<std::string, Symbol> symbolLookupTable;
};
}  // namespace dplsrc

#endif