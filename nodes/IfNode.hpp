#ifndef IFNODE_HPP
#define IFNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class IfNode : public AstNode {
   public:
    IfNode(AstNode* parent) : AstNode(parent){};
    AstNode* getCondNode() { return condNode; };
    std::vector<AstNode*> getBodyNodes() { return bodyNodes; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* condNode = nullptr;
    std::vector<AstNode*> bodyNodes;
    AstNode* elseNode = nullptr;
};

#endif