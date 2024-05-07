#include "VariableTable.hpp"

using namespace dplsrc;

void VariableTable::bind(Variable var) {
    if (scopes.empty()) {
        globalScope.insert_or_assign(var.getId(), var);
    } else {
        scopes.top().insert_or_assign(var.getId(), var);
    }
}

Variable *VariableTable::lookup(const std::string &id) {
    if (scopes.empty()) {
        return &globalScope.at(id);
    }         
    
    try {
        return &scopes.top().at(id);
    } catch (const std::out_of_range &e) {
        return &globalScope.at(id);
    }
   
}

void VariableTable::print() {
    bool isGlobal = scopes.empty();
    std::string scopeLevel = isGlobal ? "GLOBAL" : "lvl. " + std::to_string(scopes.size());

    std::cout << "\nVariable Table\n────────────────────────────────────────\n"
              << "Current scope: " << scopeLevel << "\n----------------------------------------\n";

    if (isGlobal) {
        std::cout << generatePrintString(globalScope);
    } else {
        std::cout << generatePrintString(scopes.top());
    }

    std::cout << "────────────────────────────────────────\n";
}

std::string VariableTable::generatePrintString(const Scope &scope) {
    std::string printStr;

    if (scope.empty()) {
        printStr += "EMPTY\n";
        return printStr;
    }

    for (const std::pair<const std::string, dplsrc::Variable> &entry : scope) {
        Value val = entry.second.getVal();
        printStr += entry.first + " -> " + val.toString() + " | " + val.toTypeString() + '\n';
    }

    return printStr;
}

void VariableTable::enterScope(const Scope& scope) { scopes.push(scope); }

void VariableTable::exitScope() {
    if (scopes.empty()) {
        throw std::runtime_error("Error: cannot exit global scope");
    }         
    
    scopes.pop();
}
