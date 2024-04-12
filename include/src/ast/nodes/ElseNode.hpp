#ifndef ELSENODE_HPP
#define ELSENODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class ElseNode : public AstNode {
public:
    ElseNode(AstNode *parent) : AstNode(parent) {};
    std::vector<AstNode*> getBodyNodes() { return bodyNodes; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    std::vector<AstNode*> bodyNodes;
};

#endif