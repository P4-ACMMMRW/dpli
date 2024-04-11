#ifndef TYPECHECKER_HPP
#define TYPECHECKER_HPP

#include "Symbol.hpp"
#include "SymbolTableEntry.hpp"
// #include <ASTBuilder.hpp>

namespace dplsrc {

struct ExprResult {
    Symbol type;
    SymbolTableEntry *entry = nullptr;
};

class TypeChecker {
   public:
    // visitor stuff. add when visitor is ready
    /*
    std::any visitAssignstm(AssignNode *node) override;
    std::any visitArthexpr(ArthExprNode *node) override;
    std::any visitCompexpr(CompExprNode *node) override;
    std::any visitIndex(IndexNode *node) override;
    std::any visitFiltering(FilterNode *node) override;
    std::any visitUnaryexpr(UnaryExprNode *node) override;

    */
};
}  // namespace dplsrc

#endif