#include "ProcedureTable.hpp"

using namespace dplsrc;

void ProcedureTable::bind(Procedure proc) { procedures.insert_or_assign(proc.getId(), proc); }

Procedure *ProcedureTable::lookup(const std::string &name) { return &procedures.at(name); }

void ProcedureTable::print() {
    std::cout << "\nProcedure Table\n────────────────────\n";

    if (procedures.empty()) {
        std::cout << "EMPTY\n";
    } else {
        for (const auto &entry : procedures) {
            std::cout << entry.first << " | ariety: " << entry.second.getAriety() << " (";
            std::string paramsStr = "";
            for (const auto &param : entry.second.getParams()) {
                paramsStr += param + ", ";
            }

            // Remove trailing comma and space
            if (!paramsStr.empty()) {
                paramsStr.erase(paramsStr.length() - 2);
            }

            std::cout << paramsStr << ")\n";
        }
    }

    std::cout << "────────────────────\n";
}