#include <SymbolTable.hpp>

using namespace dplsrc;

void SymbolTable::bind(Symbol sym) {
    if (sym.getVal() == "$") {
        throw std::invalid_argument("Cannot bind symbol with value: '$'\n");
    }

    table.push(sym);
    symbolLookupTable.insert_or_assign(sym.getId(), sym);
}

Symbol SymbolTable::lookup(const Symbol& sym) { return symbolLookupTable.at(sym.getId()); }

void SymbolTable::enter() { table.push(Symbol("$")); }

void SymbolTable::exit() {
    while (table.top().getVal() != "$") {
        symbolLookupTable.erase(table.top().getId());
        table.pop();
    }

    table.pop();
}