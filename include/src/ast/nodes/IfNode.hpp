#ifndef IFNODE_HPP
#define IFNODE_HPP

#include "ChildNode.hpp"
#include "ChildNodeList.hpp"

class IfNode : public AstNode {
   public:
    IfNode(std::shared_ptr<AstNode> parent)
        : AstNode(std::move(parent)),
          condNode(std::make_shared<ChildNode>()),
          bodyNodeList(std::make_shared<ChildNodeList>()),
          elseNode(std::make_shared<ChildNode>()){};

    std::shared_ptr<AstNode> getCondNode() { return condNode->getChildNode(); };
    std::vector<std::shared_ptr<AstNode>> getBodyNodes() {
        return bodyNodeList->getChildNodeList();
    };
    std::shared_ptr<AstNode> getElseNode() { return elseNode->getChildNode(); };

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<ChildNode> condNode;
    std::shared_ptr<ChildNodeList> bodyNodeList;
    std::shared_ptr<ChildNode> elseNode;
};

#endif