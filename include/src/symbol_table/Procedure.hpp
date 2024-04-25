#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <memory>
#include <vector>
#include <functional>
#include <any>

#include "Symbol.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
    /**
     * @param id the id of the procedure
     * @param params the parameters of the procedure
     * @param bodyNodes the body nodes of the procedure to be executed
     */
    Procedure(std::string id, std::vector<std::string> params,
              std::vector<std::shared_ptr<AstNode>> bodyNodes)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())),
          params(std::move(params)),
          bodyNodes(std::move(bodyNodes)) {
        ariety = this->params.size();
    }

    using ProcType = std::function<std::any(std::vector<std::shared_ptr<AstNode>>)>;
    Procedure(std::string id, std::vector<std::string> params, ProcType proc)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())), params(std::move(params)), proc(std::move(proc)), isBuiltin(true) {
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

    bool isBuiltinProcedure() const { return isBuiltin; }

    ProcType getProc() const { return proc; }

   private:
    size_t ariety = 0;
    std::vector<std::string> params;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;
    bool isBuiltin = false;
    ProcType proc;
};
}  // namespace dplsrc

#endif