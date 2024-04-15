#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <UnaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class UnaryExprNode : public UnaryNode {
   public:
    UnaryExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif