#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "Symbol.hpp"

namespace dplsrc {
class Variable : public Symbol {
   public:
    /**
     * @param id the id of the variable
    */
    Variable(std::string id) : Symbol(std::move(id)) {}

    /**
     * @param id the id of the variable
     * @param val the value of the variable
     * @param type the type of the variable
    */
    Variable(std::string id, std::string val, Type type)
        : Symbol(std::move(id)), val(std::move(val)), type(type) {}

    /**
     * @return the value of the variable
    */
    std::string getVal() const { return val; }

    /**
     * @return the type of the variable
    */
    Type getType() const { return type; }

    /**
     * @param val the value of the variable
    */
    void setVal(std::string val) { this->val = std::move(val); }

    /**
     * @param type the type of the variable
    */
    void setType(Type type) { this->type = type; }

   private:
    std::string val = "None";
    Type type = Type::NONETYPE;
};
}  // namespace dplsrc

#endif