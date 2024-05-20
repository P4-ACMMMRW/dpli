#ifndef NOTEQUALEXPRNODE_HPP
#define NOTEQUALEXPRNODE_HPP

#include "BinaryNode.hpp"

class NotEqualExprNode : public BinaryNode {
   public:
    NotEqualExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<NotEqualExprNode>(shared_from_this()));
    };
};

#endif