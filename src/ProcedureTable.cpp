#include "ProcedureTable.hpp"

using namespace dplsrc;

void ProcedureTable::bind(Procedure proc) { procedures.insert_or_assign(proc.getId(), proc); }

Procedure *ProcedureTable::lookup(const std::string &id) { return &procedures.at(id); }

void ProcedureTable::print() {
    std::cout << "\nProcedure Table\n────────────────────\n";

    if (procedures.empty()) {
        std::cout << "EMPTY\n";
    } else {
        for (const std::pair<const std::string, dplsrc::Procedure> &entry : procedures) {
            std::string idWithoutArity = entry.first.substr(0, entry.first.rfind('_'));
            std::cout << idWithoutArity << "(";

            std::string paramsStr;
            for (const std::string &param : entry.second.getParams()) {
                paramsStr += param + ", ";
            }

            // Remove trailing comma and space
            if (!paramsStr.empty()) {
                paramsStr.erase(paramsStr.length() - 2);
            }

            std::cout << paramsStr << ") | ariety: " << entry.second.getAriety() << '\n';
        }
    }

    std::cout << "────────────────────\n";
}