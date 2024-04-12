#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class LeafNode : public AstNode {
public:
    LeafNode(AstNode* parent) {AstNode::setParent(parent);}

    void print(std::string indent, std::string prefix) override;
    void addChild([[maybe_unused]] AstNode* child) override;
};

#endif