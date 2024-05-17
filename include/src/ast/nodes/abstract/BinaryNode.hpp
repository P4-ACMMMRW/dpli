#ifndef BINARYNODE_HPP
#define BINARYNODE_HPP

#include <utility>

#include "AstNode.hpp"
#include "ChildNode.hpp"

class BinaryNode : public AstNode {
   public:
    BinaryNode(std::shared_ptr<AstNode> parent)
        : AstNode(std::move(parent)),
          leftNode(std::make_shared<ChildNode>()),
          rightNode(std::make_shared<ChildNode>()) {}
    std::shared_ptr<AstNode>& getLeftNode() { return leftNode->getChildNode(); };
    std::shared_ptr<AstNode>& getRightNode() { return rightNode->getChildNode(); };

    void addChild(std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override = 0;

   private:
    std::shared_ptr<ChildNode> leftNode;
    std::shared_ptr<ChildNode> rightNode;

   protected:
    void setLeftNode(std::shared_ptr<AstNode> child) { leftNode->addChild(std::move(child)); };
    void setRightNode(std::shared_ptr<AstNode> child) { rightNode->addChild(std::move(child)); };
};

#endif