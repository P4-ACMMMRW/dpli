#ifndef TABLENODE_HPP
#define TABLENODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class TableNode : public AstNode {
    public:
     TableNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
     std::vector<std::shared_ptr<AstNode>>& getColumnNodes() { return columnNodes; };

     void addChild(std::shared_ptr<AstNode> node) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::vector<std::shared_ptr<AstNode>> columnNodes;
};

#endif