#ifndef LESSEQUALEXPRNODE_HPP
#define LESSEQUALEXPRNODE_HPP

#include "BinaryNode.hpp"

class LessEqualExprNode : public BinaryNode {
   public:
    LessEqualExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<LessEqualExprNode>(shared_from_this()));
    };
};

#endif