#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <vector>

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
    Procedure(std::string id, std::vector<std::string> params)
        : Symbol(std::move(id)), params(std::move(params)) {
        ariety = this->params.size();
    }

    int getAriety() const { return ariety; }
    std::vector<std::string> getParams() const { return params; }

   private:
    int ariety = 0;
    std::vector<std::string> params;
};
}  // namespace dplsrc

#endif