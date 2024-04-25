#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Symbol.hpp"

namespace dplsrc {
class SymbolTable {
   public:
    virtual ~SymbolTable() = default;
    
   /**  
    * Prints the state of the table to stdout
   */
    virtual void print() = 0;
};
}  // namespace dplsrc

#endif