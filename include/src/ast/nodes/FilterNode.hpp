#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class FilterNode : public AstNode {
public:
    FilterNode(AstNode *parent) : AstNode(parent) { }
    AstNode* getLeftNode()  { return left; };
    AstNode* getRightNode() { return right; };
    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* left  = nullptr;
    AstNode* right = nullptr;
};

#endif