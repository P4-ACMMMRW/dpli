#ifndef PROCDECNODE_HPP
#define PROCDECNODE_HPP

#include <ChildNode.hpp>
#include <ChildNodeList.hpp>

class ProcDecNode : public AstNode {
   public:
    ProcDecNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) { };

    std::shared_ptr<AstNode> getNameNode() { return nameNode->getChildNode(); };
    std::vector<std::shared_ptr<AstNode>>& getParamNodes() { return paramNodeList->getChildNodeList(); };
    std::vector<std::shared_ptr<AstNode>>& getBodyNodes()  { return bodyNodeList->getChildNodeList(); };

    void stopVisitingParams() { visitingParams = false; }

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    bool visitingParams = true;
    std::shared_ptr<ChildNode> nameNode;
    std::shared_ptr<ChildNodeList> paramNodeList;
    std::shared_ptr<ChildNodeList> bodyNodeList;
};

#endif