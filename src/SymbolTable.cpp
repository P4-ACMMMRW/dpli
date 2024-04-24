#include <SymbolTable.hpp>

using namespace dplsrc;

void SymbolTable::bind(Symbol sym) {
    if (sym.getId() == "$") {
        throw std::invalid_argument("Cannot bind symbol with id: '$'\n");
    }

    table.push(sym);
    symbolLookupTable.insert_or_assign(sym.getId(), sym);
}

Symbol *SymbolTable::lookup(const std::string &name) { return &symbolLookupTable.at(name); }

void SymbolTable::enter() { table.push(Symbol("$")); }

void SymbolTable::exit() {
    while (table.top().getId() != "$") {
        symbolLookupTable.erase(table.top().getId());
        table.pop();
    }

    table.pop();
}

void SymbolTable::print() {
    std::cout << "\nSymbol Table\n----------------\n";
    for (const auto &entry : symbolLookupTable) {
        std::cout << entry.first << " -> " << entry.second.getVal()<< " : " << entry.second.getType() << '\n';
    }
    std::cout << "----------------\n";
}