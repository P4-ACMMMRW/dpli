#ifndef EQUALEXPRNODE_HPP
#define EQUALEXPRNODE_HPP

#include "BinaryNode.hpp"

class EqualExprNode : public BinaryNode {
   public:
    EqualExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<EqualExprNode>(shared_from_this()));
    };
};

#endif