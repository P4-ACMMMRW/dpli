#ifndef HEADERINDEXNODE_HPP
#define HEADERINDEXNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class HeaderIndexNode : public AstNode {
public:
    HeaderIndexNode(AstNode *parent) : AstNode(parent) {}
    AstNode* getLeftNode()  { return left; };
    AstNode* getRightNode() { return right; };
    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    AstNode* left  = nullptr;
    AstNode* right = nullptr;
};

#endif