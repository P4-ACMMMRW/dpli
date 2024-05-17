#ifndef LESSEXPRNODE_HPP
#define LESSEXPRNODE_HPP

#include "BinaryNode.hpp"

class LessExprNode : public BinaryNode {
   public:
    LessExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<LessExprNode>(shared_from_this()));
    };
};

#endif