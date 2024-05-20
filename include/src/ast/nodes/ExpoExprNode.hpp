#ifndef EXPOEXPRNODE_HPP
#define EXPOEXPRNODE_HPP

#include "BinaryNode.hpp"

class ExpoExprNode : public BinaryNode {
   public:
    ExpoExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ExpoExprNode>(shared_from_this()));
    };
};

#endif