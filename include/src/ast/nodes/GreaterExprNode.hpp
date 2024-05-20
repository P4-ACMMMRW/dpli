#ifndef GREATEREXPRNODE_HPP
#define GREATEREXPRNODE_HPP

#include "BinaryNode.hpp"

class GreaterExprNode : public BinaryNode {
   public:
    GreaterExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<GreaterExprNode>(shared_from_this()));
    };
};

#endif