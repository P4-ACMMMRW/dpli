/*#include <SymbolTable.hpp>

using namespace dplsrc;

void SymbolTable::bind(Symbol s) {
    if (s.getVal() == "$") {
        throw std::invalid_argument("Cannot bind symbol with value: '$'\n");
    }

    table.push(s);
    symbolLookupTable[s.getId()] = s;
}

Symbol SymbolTable::lookup(Symbol s) {
    return symbolLookupTable[s.getId()];
}

void SymbolTable::enter() {
    table.push(Symbol("$"));
}

void SymbolTable::exit() {
    while (table.top().getVal() != "$") {
        symbolLookupTable.erase(table.top().getId());
        table.pop();
    }

    table.pop();
}*/