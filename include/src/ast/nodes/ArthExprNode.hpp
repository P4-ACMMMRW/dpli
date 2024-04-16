#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <BinaryNode.hpp>

class ArthExprNode : public BinaryNode {
   public:
    ArthExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif