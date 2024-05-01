#ifndef DIVEXPRNODE_HPP
#define DIVEXPRNODE_HPP

#include <BinaryNode.hpp>

class DivExprNode : public BinaryNode {
   public:
    DivExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<DivExprNode>(shared_from_this()));
    };
};

#endif