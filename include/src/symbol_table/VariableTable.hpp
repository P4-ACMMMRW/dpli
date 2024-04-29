#ifndef VARIABLETABLE_HPP
#define VARIABLETABLE_HPP

#include <stack>

#include "SymbolTable.hpp"
#include "Variable.hpp"

namespace dplsrc {
class VariableTable : public SymbolTable {
   public:
    /**
     * Sets up table and initializes the global scope
     */
    VariableTable() { scopes.push(Scope()); }

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
     * Variable scope where identifiers are bound to variables
     */
    using Scope = std::unordered_map<std::string, Variable>;

    /**
     * Enters a new variable scope
     * @param VariableTable The table to copy the scope from
     */
    void enterScope(Scope scope);

    /**
     * Exits the current variable scope
     */
    void exitScope();

    /**
     * @return The top scope of the vtable
     */
    Scope top() { return scopes.top(); }

   private:
    std::stack<Scope> scopes;
};
}  // namespace dplsrc

#endif