#ifndef IFNODE_HPP
#define IFNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class IfNode : public AstNode {
    public:
     IfNode(std::shared_ptr<AstNode> parent) : AstNode(parent){};
     std::shared_ptr<AstNode> getCondNode() { return condNode; };
     std::vector<std::shared_ptr<AstNode>> getBodyNodes() { return bodyNodes; };

     void addChild(std::shared_ptr<AstNode> node) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> condNode = nullptr;
     std::vector<std::shared_ptr<AstNode>> bodyNodes;
     std::shared_ptr<AstNode> elseNode = nullptr;
};

#endif