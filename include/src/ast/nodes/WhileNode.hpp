#ifndef WHILENODE_HPP
#define WHILENODE_HPP

#include <ChildNode.hpp>
#include <ChildNodeList.hpp>

class WhileNode : public AstNode {
   public:
    WhileNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {};
    std::shared_ptr<AstNode> getChildNode()                  { return childNode->getChildNode(); };
    std::vector<std::shared_ptr<AstNode>> getChildNodeList() { return childNodeList->getChildNodeList(); };

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<ChildNode>     childNode;
    std::shared_ptr<ChildNodeList> childNodeList;
};

#endif