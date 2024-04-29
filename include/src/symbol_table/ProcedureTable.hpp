#ifndef PROCEDURETABLE_HPP
#define PROCEDURETABLE_HPP

#include "Procedure.hpp"
#include "ProcId.hpp"
#include "SymbolTable.hpp"

namespace dplsrc {
class ProcedureTable : public SymbolTable {
   public:
    /**
     * Binds a procedure to the table
     * @param proc The procedure to bind
     */
    void bind(Procedure proc);

    /**
     * Looks up a procedure in the table by id
     * @param id The id of the procedure to look up
     * @return A pointer to the procedure
     */
    Procedure *lookup(const ProcId &id);

    /**
     * Prints the state of the table to stdout
     */
    void print() override;

   private:
    std::unordered_map<std::string, Procedure> procedures;
};
}  // namespace dplsrc

#endif