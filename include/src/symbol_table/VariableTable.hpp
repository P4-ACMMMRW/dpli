#ifndef VARIABLETABLE_HPP
#define VARIABLETABLE_HPP

#include <stack>

#include "SymbolTable.hpp"
#include "Variable.hpp"

namespace dplsrc {
class VariableTable : public SymbolTable {
   public:
    /**
     * Default constructor
     */
    VariableTable() { enterScope(); }

    /**
     * Binds a variable to the table
     * @param var The variable to bind
     */
    void bind(Variable var);

    /**
     * Looks up a variable in the table by id
     * @param id The id of the variable to look up
     * @return A pointer to the variable
     */
    Variable *lookup(const std::string &id);

    /**
     * Prints the state of the table to stdout
     */
    void print() override;

    /**
     * Enters a new variable scope
     */
    void enterScope();

    /**
     * Exits the current variable scope
     */
    void exitScope();

   private:
    std::stack<std::unordered_map<std::string, Variable>> scopes;
};
}  // namespace dplsrc

#endif