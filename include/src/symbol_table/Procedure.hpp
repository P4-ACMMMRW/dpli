#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <memory>
#include <vector>

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
    /**
     * @param id the id of the procedure
     * @param params the parameters of the procedure
     */
    Procedure(std::string id, std::vector<std::string> params,
              std::vector<std::shared_ptr<AstNode>> bodyNodes)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())),
          params(std::move(params)),
          bodyNodes(std::move(bodyNodes)) {
        ariety = this->params.size();
    }

    /**
     * @return the ariety of the procedure
     */
    size_t getAriety() const { return ariety; }

    /**
     * @return the parameters of the procedure as a vector of strings
     */
    std::vector<std::string> getParams() const { return params; }

    /**
     * @return the body nodes of the procedure as a vector of shared pointers to AstNodes
     */
    std::vector<std::shared_ptr<AstNode>> getBodyNodes() const { return bodyNodes; }

   private:
    size_t ariety = 0;
    std::vector<std::string> params;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;
};
}  // namespace dplsrc

#endif