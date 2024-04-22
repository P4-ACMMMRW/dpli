#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <utility>
#include "SymbolType.hpp"
#include "../ast/nodes/abstract/AstNode.hpp"

namespace dplsrc {


class Symbol {
   public:
    Symbol(std::string val) : val(std::move(val)) {}
    Symbol(std::string id, std::string val) : id(std::move(id)), val(std::move(val)) {}
    std::string getId() const { return id; }
    std::string getVal() const { return val; }


    Symbol(std::string name, SymbolType type, ASTNode *declNode)
        : name(std::move(name)), type(std::move(type)), declNode(declNode) {}

    


    void setEvaluatedSymbolType(const SymbolType &symbolType) { this->symbolType = symbolType; }

    const SymbolType &getEvaluatedSymbolType() const {
    if (!symbolType.is(TYPE_INVALID))
      return symbolType;
    if (children.size() != 1)
      throw std::runtime_error("Cannot deduce evaluated symbol type");
    return children.front()->getEvaluatedSymbolType();
  }

    const std::string name;
    SymbolType type = SymbolType(TYPE_INVALID);
    AstNode *declNode;
    AstNode *parent;
    std::vector<AstNode *> children;
    SymbolType symbolType = SymbolType(TYPE_INVALID);
   private:
    std::string id;
    std::string val;
    
};
}  // namespace dplsrc

#endif