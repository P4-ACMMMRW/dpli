#ifndef UNARYNODE_HPP
#define UNARYNODE_HPP

#include <ChildNode.hpp>
#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class UnaryNode : public AstNode {
   public:
    UnaryNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
    std::shared_ptr<AstNode>& getChildNode() { return childNode->getChildNode(); };

    void addChild(std::shared_ptr<AstNode> child) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::shared_ptr<ChildNode> childNode;
};

#endif