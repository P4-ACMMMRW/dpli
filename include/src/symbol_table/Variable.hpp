#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Symbol.hpp"

namespace dplsrc {
class Variable : public Symbol {
   public:
    Variable(std::string id) : Symbol(std::move(id)) {}
    Variable(std::string id, std::string val, Type type)
        : Symbol(std::move(id)), val(std::move(val)), type(type) {}

    std::string getVal() const { return val; }
    Type getType() const { return type; }

    void setVal(std::string val) { this->val = std::move(val); }
    void setType(Type type) { this->type = type; }

   private:
    std::string val = "None";
    Type type = Type::NONETYPE;
};
}  // namespace dplsrc

#endif