#ifndef TABLENODE_HPP
#define TABLENODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class TableNode : public AstNode {
public:
    TableNode(AstNode *parent) : AstNode(parent) {}
    std::vector<AstNode*> getColumnNodes() { return columnNodes; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    std::vector<AstNode*> columnNodes;
};

#endif