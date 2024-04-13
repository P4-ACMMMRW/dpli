#ifndef ARTHEXPRNODE_HPP
#define ARTHEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ArthExprNode : public AstNode {
    public:
     ArthExprNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
     std::shared_ptr<AstNode>& getLeft() { return left; };
     std::shared_ptr<AstNode>& getRight() { return right; };

     void addChild(std::shared_ptr<AstNode> child) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> left = nullptr;
     std::shared_ptr<AstNode> right = nullptr;
};

#endif