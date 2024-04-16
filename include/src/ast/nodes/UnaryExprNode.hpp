#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <UnaryNode.hpp>

class UnaryExprNode : public UnaryNode {
   public:
    UnaryExprNode(std::shared_ptr<AstNode> parent) : UnaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif