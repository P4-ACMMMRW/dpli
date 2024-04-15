#ifndef COMPEXPRNODE_HPP
#define COMPEXPRNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class CompExprNode : public BinaryNode {
   public:
    CompExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
 
    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif