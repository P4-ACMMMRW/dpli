#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ArthExprNode : public AstNode {
   public:
    ArthExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
    std::shared_ptr<AstNode>& getLeftNode() { return leftNode; };
    std::shared_ptr<AstNode>& getRightNode() { return rightNode; };

    void addChild(std::shared_ptr<AstNode> child) override;

    void print(std::string indent, std::string prefix) override;

    void accept(AstVisitor* visitor) override;

   private:
    std::shared_ptr<AstNode> leftNode = nullptr;
    std::shared_ptr<AstNode> rightNode = nullptr;
};

#endif