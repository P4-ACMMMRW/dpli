#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
    Procedure(std::string id, int ariety)
        : Symbol(std::move(id)), ariety(ariety) {}

    int getAriety() const { return ariety; }

    void setAriety(int ariety) { this->ariety = ariety; }

   private:
    int ariety = 0;
};
}  // namespace dplsrc

#endif