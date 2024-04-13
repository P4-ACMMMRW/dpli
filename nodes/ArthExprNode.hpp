#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class ArthExprNode : public AstNode {
   public:
    ArthExprNode(AstNode* parent) : AstNode(parent) {}
    AstNode* getLeft() { return left; };
    AstNode* getRight() { return right; };

    void addChild(AstNode* child) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif