#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <utility>

#include "AstNode.hpp"
#include "Type.hpp"

namespace dplsrc {
class Symbol {
   public:
    Symbol(std::string id) : id(std::move(id)) {}
    Symbol(std::string id, std::string val, Type type)
        : id(std::move(id)), val(std::move(val)), type(type) {}

    std::string getId() const { return id; }
    std::string getVal() const { return val; }
    Type getType() const { return type; }

    void setVal(std::string val) { this->val = std::move(val); }
    void setType(Type type) { this->type = type; }

   private:
    std::string id;
    std::string val;
    Type type = Type(Type::UNKNOWN);
};
}  // namespace dplsrc

#endif