#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

#include "AstNode.hpp"
#include "Type.hpp"

namespace dplsrc {
class Symbol {
   public:
    // Rule of five
    virtual ~Symbol() = default;
    Symbol(const Symbol& other) = default;
    Symbol(Symbol&& other) noexcept = default;
    Symbol& operator=(const Symbol& other) = default;
    Symbol& operator=(Symbol&& other) noexcept = default;

    /**
     * @param id the id of the symbol
     */
    Symbol(std::string id) : id(std::move(id)) {}

    /**
     * @return the id of the symbol
     */
    std::string getId() const { return id; }

   private:
    std::string id;
};
}  // namespace dplsrc

#endif