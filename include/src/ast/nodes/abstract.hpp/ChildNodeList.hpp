#ifndef STMNODE_HPP
#define CHILDNODELIST_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ChildNodeList : AstNode {
   public:
    ChildNodeList(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};

    std::vector<std::shared_ptr<AstNode>> getChildNodeList() { return childNodeList; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::vector<std::shared_ptr<AstNode>> childNodeList;
};

#endif