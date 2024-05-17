#ifndef INTERSECTIONEXPRNODE_HPP
#define INTERSECTIONEXPRNODE_HPP

#include "BinaryNode.hpp"

class IntersectionExprNode : public BinaryNode {
   public:
    IntersectionExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<IntersectionExprNode>(shared_from_this()));
    };
};

#endif