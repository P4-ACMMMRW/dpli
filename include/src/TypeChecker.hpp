#ifndef TYPECHECKER_HPP
#define TYPECHECKER_HPP

#include "Symbol.hpp"
#include "SymbolTableEntry.hpp"
#include "SymbolTable.hpp"
// #include <ASTVisitor.hpp>

namespace dplsrc {

struct ExprResult {
    Symbol type;
    SymbolTableEntry *entry = nullptr;
};

class TypeChecker {
   public:
  
    std::any visitAssignstm(AssignNode *node) override;
    std::any visitArthexpr(ArthExprNode *node) override;
    std::any visitCompexpr(CompExprNode *node) override;
    std::any visitFiltering(FilterNode *node) override;
    std::any visitIndex(IndexNode *node) override;
    std::any visitNotexpr(NotNode *node) override;
    std::any visitUnaryexpr(UnaryExprNode *node) override;
    std::any visitWhilestm(WhileNode *node) override;

};
}  // namespace dplsrc

#endif