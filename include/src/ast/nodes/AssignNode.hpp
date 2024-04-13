#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class AssignNode : public AstNode {
   public:
    AssignNode(std::shared_ptr<AstNode> parent) : left(nullptr), right(nullptr) { AstNode::setParent(parent); }
    std::shared_ptr<AstNode> getLeft() { return left; };
    std::shared_ptr<AstNode> getRight() { return right; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::shared_ptr<AstNode> left = nullptr;
    std::shared_ptr<AstNode> right = nullptr;
};

#endif