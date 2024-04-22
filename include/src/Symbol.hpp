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


    Symbol(std::string name, SymbolType type, AstNode *declNode)
        : name(std::move(name)), type(std::move(type)), declNode(declNode) {}


    const std::string name;
    SymbolType type = SymbolType(SymbolSuperType::TYPE_INVALID);
    AstNode *declNode;

 
   private:
    std::string id;
    std::string val;
    
};
}  // namespace dplsrc

#endif