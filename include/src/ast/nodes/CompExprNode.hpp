#ifndef COMPEXPRNODE_HPP
#define COMPEXPRNODE_HPP

#include <BinaryNode.hpp>

class CompExprNode : public BinaryNode {
   public:
    CompExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif