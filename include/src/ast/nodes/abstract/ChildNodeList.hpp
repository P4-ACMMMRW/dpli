#ifndef CHILDNODELIST_HPP
#define CHILDNODELIST_HPP

#include <AstNode.hpp>
#include <vector>

class ChildNodeList : public AstNode {
   public:
    ChildNodeList() {};

    std::vector<std::shared_ptr<AstNode>>& getChildNodeList() { return childNodeList; };

    void addChild(std::shared_ptr<AstNode> node) override;

    std::string print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override; 

   private:
    std::vector<std::shared_ptr<AstNode>> childNodeList;
};

#endif