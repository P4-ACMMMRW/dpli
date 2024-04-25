#include "VariableTable.hpp"

using namespace dplsrc;

void VariableTable::bind(Variable var) { scopes.top().insert_or_assign(var.getId(), var); }

Variable *VariableTable::lookup(const std::string &name) { return &scopes.top().at(name); }

void VariableTable::print() {
    std::cout << "\nVariable Table\n----------------\n"
              << "Current scope: " << scopes.size() << '\n';

    if (scopes.top().empty()) {
        std::cout << "EMPTY\n";
    } else {
        for (const auto &entry : scopes.top()) {
            std::cout << entry.first << " -> " << entry.second.getVal() << " : "
                      << entry.second.getType() << '\n';
        }
    }

    std::cout << "----------------\n";
}

void VariableTable::enterScope() {
    if (scopes.empty()) {
        scopes.push(std::unordered_map<std::string, Variable>());
    } else {
        scopes.push(scopes.top());
    }
}

void VariableTable::exitScope() {
    if (scopes.size() > 1) {
        scopes.pop();
    } else {
        throw std::logic_error("Error: cannot exit global scope");
    }
}
