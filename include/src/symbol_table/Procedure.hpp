#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <vector>
#include <memory>

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
   /**
    * @param id the id of the procedure
    * @param params the parameters of the procedure
   */
    Procedure(std::string id, std::vector<std::string> params, std::vector<std::shared_ptr<AstNode>> bodyNodes)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())), params(std::move(params)), bodyNodes(std::move(bodyNodes)) {
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

    /**
     * @return the body nodes of the procedure as a vector of shared pointers to AstNodes
    */
    std::vector<std::shared_ptr<AstNode>> getBodyNodes() const { return bodyNodes; }

   private:
    int ariety = 0;
    std::vector<std::string> params;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;

};
}  // namespace dplsrc

#endif