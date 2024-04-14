#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class AssignNode : public AstNode {
   public:
    AssignNode(std::shared_ptr<AstNode> parent) : leftNode(nullptr), rightNode(nullptr) {
        AstNode::setParent(std::move(parent));
    }
    std::shared_ptr<AstNode> getLeftNode() { return leftNode; };
    std::shared_ptr<AstNode> getRightNode() { return rightNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<AstNode> leftNode = nullptr;
    std::shared_ptr<AstNode> rightNode = nullptr;
};

#endif