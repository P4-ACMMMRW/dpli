#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class AssignNode : public AstNode {
public:
    AssignNode(AstNode* parent) : left(nullptr), right(nullptr) {AstNode::setParent(parent);}
    AstNode* getLeft() { return  left;  };
    AstNode* getRight() { return right; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* left = nullptr;
    AstNode* right = nullptr;
};

#endif