#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Symbol.hpp"
#include "Value.hpp"

namespace dplsrc {
class Variable : public Symbol {
   public:
    /**
     * @param id the id of the variable
     * @param val the value of the variable
     * @param type the type of the variable
     */
    Variable(std::string id, Value val, Type type)
        : Symbol(std::move(id)), val(std::move(val)), type(type) {}

    /**
     * @return the value of the variable
     */
    Value getVal() const { return val; }

    /**
     * @return the type of the variable
     */
    Type getType() const { return type; }

    /**
     * @param val the value of the variable
     */
    void setVal(Value val) { this->val = std::move(val); }

    /**
     * @param type the type of the variable
     */
    void setType(Type type) { this->type = type; }

   private:
    Value val;
    Type type = Type::NONETYPE;
};
}  // namespace dplsrc

#endif