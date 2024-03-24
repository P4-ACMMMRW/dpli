#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <stack>
#include <unordered_map>
#include <stdexcept>

#include "Symbol.hpp"

namespace dplsrc {
    class SymbolTable {
        public:
            void bind(Symbol s);
            Symbol lookup(Symbol s);
            void enter();
            void exit();

        private:
            std::stack<Symbol> table;
            std::unordered_map<std::string, Symbol> symbolLookupTable;
    };
}

#endif