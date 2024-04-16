#ifndef JUNCEXPRNODE_HPP
#define JUNCEXPRNODE_HPP

#include <BinaryNode.hpp>

class JuncExprNode : public BinaryNode {
   public:
    JuncExprNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif