#ifndef PARNODE_HPP
#define PARNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>


class ParNode : public AstNode {
public:
    ParNode(AstNode *parent) : AstNode(parent) {}
    AstNode* getChildNode() { return childNode; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* childNode = nullptr;
};

#endif