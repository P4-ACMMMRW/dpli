#ifndef LEAFNODE_HPP
#define LEAFNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class LeafNode : public AstNode {
   public:
    LeafNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    void print(std::string indent, std::string prefix) override;
    void addChild([[maybe_unused]] std::shared_ptr<AstNode> child) override;
};

#endif