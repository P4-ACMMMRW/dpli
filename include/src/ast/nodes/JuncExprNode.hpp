#ifndef JUNCEXPRNODE_HPP
#define JUNCEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class JuncExprNode : public AstNode {
   public:
    JuncExprNode(AstNode* parent) : AstNode(parent) {}

    AstNode* getLeft() { return left; };
    AstNode* getRight() { return right; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif