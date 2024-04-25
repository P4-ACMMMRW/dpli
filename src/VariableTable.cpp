#include "VariableTable.hpp"

using namespace dplsrc;

void VariableTable::bind(Variable var) { scopes.top().insert_or_assign(var.getId(), var); }

Variable *VariableTable::lookup(const std::string &id) { return &scopes.top().at(id); }

void VariableTable::print() {
    std::string scopeLevel =
        scopes.size() == 1 ? "GLOBAL" : "lvl. " + std::to_string(scopes.size() - 1);

    std::cout << "\nVariable Table\n────────────────────\n"
              << "Current scope: " << scopeLevel << "\n--------------------\n";

    if (scopes.top().empty()) {
        std::cout << "EMPTY\n";
    } else {
        for (const auto &entry : scopes.top()) {
            std::cout << entry.first << " -> " << entry.second.getVal() << " | "
                      << entry.second.getType() << '\n';
        }
    }

    std::cout << "────────────────────\n";
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
        throw std::runtime_error("Error: cannot exit global scope");
    }
}
