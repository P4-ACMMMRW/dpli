#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class FilterNode : public AstNode {
    public:
     FilterNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
     std::shared_ptr<AstNode>& getLeftNode() { return left; };
     std::shared_ptr<AstNode>& getRightNode() { return right; };
     void addChild(std::shared_ptr<AstNode> node) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> left = nullptr;
     std::shared_ptr<AstNode> right = nullptr;
};

#endif