#ifndef RUTURNNODE_HPP
#define RUTURNNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class ReturnNode : public AstNode {
public:
    ReturnNode(AstNode *parent) : AstNode(parent) { };
    AstNode* getchild() { return child; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* child = nullptr;
};

#endif