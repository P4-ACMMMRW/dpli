#ifndef OREXPRNODE_HPP
#define OREXPRNODE_HPP

#include <BinaryNode.hpp>

class OrExprNode : public BinaryNode {
   public:
    OrExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<OrExprNode>(shared_from_this()));
    };
};

#endif