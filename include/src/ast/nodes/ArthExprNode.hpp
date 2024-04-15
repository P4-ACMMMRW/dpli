#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ArthExprNode : public BinaryNode {
   public:
    ArthExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif