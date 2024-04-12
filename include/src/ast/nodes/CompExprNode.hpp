#ifndef COMPEXPRNODE_HPP
#define COMPEXPRNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class CompExprNode : public AstNode {
public:
    CompExprNode(AstNode* parent) : AstNode(parent) {}
    AstNode* getLeft() { return  left;  };
    AstNode* getRight() { return right; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif