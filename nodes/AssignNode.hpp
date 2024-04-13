#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class AssignNode : public AstNode {
   public:
    AssignNode(AstNode* parent) : left(nullptr), right(nullptr) { AstNode::setParent(parent); }
    AstNode* getLeft() { return left; };
    AstNode* getRight() { return right; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif