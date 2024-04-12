#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class UnaryExprNode : public AstNode {
   public:
    UnaryExprNode(AstNode* parent) : AstNode(parent) {}
    AstNode* getchild() { return child; };

    void addChild(AstNode* child) override;

    void print(std::string indent, std::string prefix);

   private:
    AstNode* child = nullptr;
};

#endif