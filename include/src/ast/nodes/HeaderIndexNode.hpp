#ifndef HEADERINDEXNODE_HPP
#define HEADERINDEXNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class HeaderIndexNode : public AstNode {
   public:
    HeaderIndexNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}
    std::shared_ptr<AstNode>& getLeftNode() { return left; };
    std::shared_ptr<AstNode>& getRightNode() { return right; };
    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::shared_ptr<AstNode> left = nullptr;
    std::shared_ptr<AstNode> right = nullptr;
};

#endif