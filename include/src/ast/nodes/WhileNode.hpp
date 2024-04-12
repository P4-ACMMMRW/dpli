#ifndef WHILENODE_HPP
#define WHILENODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class WhileNode : public AstNode {
public:
    WhileNode(AstNode *parent) : AstNode(parent) {};
    AstNode*              getCondNode() { return condNode; };
    std::vector<AstNode*> getStmNodes() { return stmNodes; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* condNode = nullptr;
    std::vector<AstNode*> stmNodes;
};

#endif