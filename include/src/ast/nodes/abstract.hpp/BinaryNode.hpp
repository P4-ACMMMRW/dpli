#ifndef BINARYNODE_HPP
#define BINARYNODE_HPP

#include <ChildNode.hpp>
#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class BinaryNode : public AstNode {
   public:
    BinaryNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
    std::shared_ptr<AstNode>& getLeftNode() { return leftNode->getChildNode(); };
    std::shared_ptr<AstNode>& getRightNode() { return rightNode->getChildNode(); };

    void addChild(std::shared_ptr<AstNode> child) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::shared_ptr<ChildNode> leftNode;
    std::shared_ptr<ChildNode> rightNode;
};

#endif