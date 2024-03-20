#include "SymbolTable.hpp"

using namespace dplsrc;

void SymbolTable::enter() {
    table.push("$");
}

void SymbolTable::exit() {
    while (table.top() != "$") {
        table.pop();
    }

    table.pop();
}