#ifndef JUNCEXPRNODE_HPP
#define JUNCEXPRNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class JuncExprNode : public BinaryNode {
   public:
    JuncExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif