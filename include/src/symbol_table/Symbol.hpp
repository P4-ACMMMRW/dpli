#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

#include "AstNode.hpp"
#include "Type.hpp"

namespace dplsrc {
class Symbol {
   public:
    Symbol(std::string id) : id(std::move(id)) {}

    std::string getId() const { return id; }

   private:
    std::string id;
};
}  // namespace dplsrc

#endif