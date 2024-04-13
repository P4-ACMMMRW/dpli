#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ListNode : public AstNode {
   public:
    ListNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) { setText("[]"); }
    std::vector<std::shared_ptr<AstNode>>& getChildren() { return children; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::vector<std::shared_ptr<AstNode>> children;
};

#endif