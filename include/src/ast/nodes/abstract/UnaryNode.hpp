#ifndef UNARYNODE_HPP
#define UNARYNODE_HPP

#include "AstNode.hpp"
#include "ChildNode.hpp"

class UnaryNode : public AstNode {
   public:
    UnaryNode(std::shared_ptr<AstNode> parent)
        : AstNode(std::move(parent)), childNode(std::make_shared<ChildNode>()) {}
    std::shared_ptr<AstNode>& getChildNode() { return childNode->getChildNode(); };

    void addChild(std::shared_ptr<AstNode> child) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override = 0;

   private:
    std::shared_ptr<ChildNode> childNode;
};

#endif