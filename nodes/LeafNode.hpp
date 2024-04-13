#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class LeafNode : public AstNode {
   public:
    LeafNode(AstNode* parent) { AstNode::setParent(parent); }

    void print(std::string indent, std::string prefix) override;
    void addChild([[maybe_unused]] AstNode* child) override;
};

#endif