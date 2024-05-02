#ifndef VARIABLE
#define VARIABLE

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
    Variable(std::string id, Value val)
        : Symbol(std::move(id)), val(std::move(val)) {}

    /**
     * @return the value of the variable
     */
    Value getVal() const { return val; }

    /**
     * @param val the value of the variable
     */
    void setVal(Value val) { this->val = std::move(val); }

   private:
    Value val;
};
}  // namespace dplsrc

#endif
