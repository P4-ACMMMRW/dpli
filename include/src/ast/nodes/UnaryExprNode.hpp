#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class UnaryExprNode : public AstNode {
   public:
    UnaryExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
    std::shared_ptr<AstNode> getChildNode() { return childNode; };

    void addChild(std::shared_ptr<AstNode> child) override;

    void print(std::string indent, std::string prefix) override;

    void accept(AstVisitor* visitor) override;

   private:
    std::shared_ptr<AstNode> childNode = nullptr;
};

#endif