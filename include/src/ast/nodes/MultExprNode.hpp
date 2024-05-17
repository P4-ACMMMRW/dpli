#ifndef MULTEXPRNODE_HPP
#define MULTEXPRNODE_HPP

#include "BinaryNode.hpp"

class MultExprNode : public BinaryNode {
   public:
    MultExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<MultExprNode>(shared_from_this()));
    };
};

#endif