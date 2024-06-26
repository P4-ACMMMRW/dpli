#ifndef PROCEDURE_HPP
#define PROCEDURE_HPP

#include <any>
#include <functional>
#include <memory>
#include <vector>

#include "Symbol.hpp"
#include "Value.hpp"
#include "VariableTable.hpp"

namespace dplsrc {
class Procedure : public Symbol {
   public:
    /**
     * Constructor for user-defined procedures
     * @param id the id of the procedure
     * @param params the parameters of the procedure
     * @param bodyNodes the body nodes of the procedure to be executed
     */
    Procedure(std::string id, std::vector<std::string> params,
              std::vector<std::shared_ptr<AstNode>> bodyNodes)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())),
          arity(params.size()),
          params(std::move(params)),
          bodyNodes(std::move(bodyNodes)) {}

    /**
     * Constructor for user-defined procedures
     * @param id the id of the procedure
     * @param params the parameters of the procedure
     * @param bodyNodes the body nodes of the procedure to be executed
     * @param scope the variable table of the procedure at the time of definition
     */
    Procedure(std::string id, std::vector<std::string> params,
              std::vector<std::shared_ptr<AstNode>> bodyNodes, VariableTable::Scope scope)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())),
          arity(params.size()),
          params(std::move(params)),
          bodyNodes(std::move(bodyNodes)),
          scope(std::move(scope)) {}

    /**
     * Function type for built-in procedures that take a vector of shared pointers to AstNodes as
     * input and return any type
     */
    using ProcType = std::function<Value(std::vector<std::shared_ptr<AstNode>>)>;

    /**
     * Constructor for built-in procedures
     * @param id the id of the procedure
     * @param params the parameters of the procedure
     * @param proc the built-in procedure to be executed
     */
    Procedure(std::string id, std::vector<std::string> params, ProcType proc)
        : Symbol(std::move(id) + "_" + std::to_string(params.size())),
          arity(params.size()),
          params(std::move(params)),
          proc(std::move(proc)),
          isBuiltin(true) {}

    /**
     * @return the arity of the procedure
     */
    size_t getArity() const { return arity; }

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

    VariableTable::Scope getScope() const { return scope; }

   private:
    size_t arity = 0;
    std::vector<std::string> params;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;
    ProcType proc;
    bool isBuiltin = false;
    VariableTable::Scope scope;
};
}  // namespace dplsrc

#endif