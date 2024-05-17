#ifndef MINUSEXPRNODE_HPP
#define MINUSEXPRNODE_HPP

#include "BinaryNode.hpp"

class MinusExprNode : public BinaryNode {
   public:
    MinusExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<MinusExprNode>(shared_from_this()));
    };
};

#endif