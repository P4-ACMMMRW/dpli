#ifndef TABLENODE_HPP
#define TABLENODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class TableNode : public AstNode {
   public:
    TableNode(AstNode* parent) : AstNode(parent) {}
    std::vector<AstNode*> getColumnNodes() { return columnNodes; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::vector<AstNode*> columnNodes;
};

#endif