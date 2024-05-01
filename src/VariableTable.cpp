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
    } else {
        try {
            return &scopes.top().at(id);
        } catch (const std::out_of_range &e) {
            return &globalScope.at(id);
        }
    }
}

void VariableTable::print() {
    std::string scopeLevel =
        scopes.empty() ? "GLOBAL" : "lvl. " + std::to_string(scopes.size());

    std::cout << "\nVariable Table\n────────────────────────────────────────\n"
              << "Current scope: " << scopeLevel << "\n----------------------------------------\n";

    if (scopes.empty()) {
        if (globalScope.empty()) {
            std::cout << "EMPTY\n";
        } else {
            for (const std::pair<const std::string, dplsrc::Variable> &entry : globalScope) {
                std::cout << entry.first << " -> " << entry.second.getVal().toString()
                        << " | type: " << entry.second.getType() << '\n';
            }
        }
    } else {
        if (scopes.top().empty()) {
            std::cout << "EMPTY\n";
        } else {
            for (const std::pair<const std::string, dplsrc::Variable> &entry : scopes.top()) {
                std::cout << entry.first << " -> " << entry.second.getVal().toString()
                        << " | type: " << entry.second.getType() << '\n';
            }
        }
    }

    std::cout << "────────────────────────────────────────\n";
}

void VariableTable::enterScope(Scope scope) { scopes.push(scope); }

void VariableTable::exitScope() {
    if (scopes.empty()) {
        throw std::runtime_error("Error: cannot exit global scope");
    } else {
        scopes.pop();
    }
}
