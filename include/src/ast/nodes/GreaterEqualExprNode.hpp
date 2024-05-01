#ifndef GREATEREQUALEXPRNODE_HPP
#define GREATEREQUALEXPRNODE_HPP

#include <BinaryNode.hpp>

class GreaterEqualExprNode : public BinaryNode {
   public:
    GreaterEqualExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<GreaterEqualExprNode>(shared_from_this()));
    };
};

#endif