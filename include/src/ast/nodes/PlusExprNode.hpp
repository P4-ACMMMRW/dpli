#ifndef PLUSEXPRNODE_HPP
#define PLUSEXPRNODE_HPP

#include "BinaryNode.hpp"

class PlusExprNode : public BinaryNode {
   public:
    PlusExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<PlusExprNode>(shared_from_this()));
    };
};

#endif