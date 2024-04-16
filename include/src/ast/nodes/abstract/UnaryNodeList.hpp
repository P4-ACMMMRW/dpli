#ifndef UNARYNODELIST_HPP
#define UNARYNODELIST_HPP

#include <AstNode.hpp>
#include <ChildNodeList.hpp>

class UnaryNodeList : public AstNode {
   public:
    UnaryNodeList(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)), 
                                                     childNodeList(std::make_shared<ChildNodeList>()) { }
    std::vector<std::shared_ptr<AstNode>>& getChildNodeList() { return childNodeList->getChildNodeList(); };

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix);

    void accept(std::shared_ptr<AstVisitor> visitor) override = 0;

   private:
    std::shared_ptr<ChildNodeList> childNodeList;
};

#endif