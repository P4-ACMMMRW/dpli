#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class UnaryExprNode : public AstNode {
public:
    UnaryExprNode(AstNode* parent) : AstNode(parent) { }
    AstNode* getchild() { return child; };

    void addChild(AstNode* child) override;

    void print(std::string indent, std::string prefix);
private:
    AstNode* child = nullptr;
};

#endif