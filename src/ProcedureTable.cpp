#include "ProcedureTable.hpp"

using namespace dplsrc;

void ProcedureTable::bind(Procedure proc) { procedures.insert_or_assign(proc.getId(), proc); }

Procedure *ProcedureTable::lookup(const std::string &name) { return &procedures.at(name); }

void ProcedureTable::print() {
    std::cout << "\nProcedure Table\n----------------\n";

    if (procedures.empty()) {
        std::cout << "EMPTY\n";
    } else {
        for (const auto &entry : procedures) {
            std::cout << entry.first << " | params: " << entry.second.getAriety() << '\n';
        }
    }

    std::cout << "----------------\n";
}