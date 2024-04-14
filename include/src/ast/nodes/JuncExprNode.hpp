#ifndef JUNCEXPRNODE_HPP
#define JUNCEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class JuncExprNode : public AstNode {
   public:
    JuncExprNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    std::shared_ptr<AstNode>& getLeftNode() { return leftNode; };
    std::shared_ptr<AstNode>& getRightNode() { return rightNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<AstNode> leftNode;
    std::shared_ptr<AstNode> rightNode;
};

#endif