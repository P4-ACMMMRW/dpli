#ifndef UNIONEXPRNODE_HPP
#define UNIONEXPRNODE_HPP

#include <BinaryNode.hpp>

class UnionExprNode : public BinaryNode {
   public:
    UnionExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<UnionExprNode>(shared_from_this()));
    };
};

#endif