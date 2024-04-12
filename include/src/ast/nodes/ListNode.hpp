#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class ListNode : public AstNode {
public:
    ListNode(AstNode *parent) : AstNode(parent) {setText("[]");}
    std::vector<AstNode*> getChildren() { return children; };
    
    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;
private:
    std::vector<AstNode*> children;
};

#endif