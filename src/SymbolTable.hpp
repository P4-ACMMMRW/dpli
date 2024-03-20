#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <stack>

namespace dplsrc {
    class SymbolTable {
        public:
            void bind(std::string id, std::string val);
            std::string lookup(std::string id);
            void enter();
            void exit();

        private:
            std::stack<std::string> table;
    };
}

#endif