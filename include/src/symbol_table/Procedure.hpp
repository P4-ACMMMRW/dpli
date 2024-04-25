#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <vector>

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
   /**
    * @param id the id of the procedure
    * @param params the parameters of the procedure
   */
    Procedure(std::string id, std::vector<std::string> params)
        : Symbol(std::move(id)), params(std::move(params)) {
        ariety = this->params.size();
    }

    /**
     * @return the ariety of the procedure
    */
    int getAriety() const { return ariety; }

    /**
     * @return the parameters of the procedure as a vector of strings
    */
    std::vector<std::string> getParams() const { return params; }

   private:
    int ariety = 0;
    std::vector<std::string> params;
};
}  // namespace dplsrc

#endif