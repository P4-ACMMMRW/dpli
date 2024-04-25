#ifndef VARIABLETABLE_HPP
#define VARIABLETABLE_HPP

#include <stack>
#include "SymbolTable.hpp"
#include "Variable.hpp"

namespace dplsrc {
class VariableTable : public SymbolTable {
   public:
    VariableTable() { enterScope(); }

    void bind(Variable var);
    Variable *lookup(const std::string &name);
    void print() override;

    void enterScope();
    void exitScope();

   private:
    std::stack<std::unordered_map<std::string, Variable>> scopes;
};
}  // namespace dplsrc

#endif