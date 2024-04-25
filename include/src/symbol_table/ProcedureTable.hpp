#ifndef PROCEDURETABLE_HPP
#define PROCEDURETABLE_HPP

#include "SymbolTable.hpp"
#include "Procedure.hpp"

namespace dplsrc {
class ProcedureTable : public SymbolTable {
   public:
    void bind(Procedure proc);
    Procedure *lookup(const std::string &name);
    void print() override;

   private:
    std::unordered_map<std::string, Procedure> procedures;
};
}  // namespace dplsrc

#endif