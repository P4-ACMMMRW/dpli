#ifndef NOTNODE_HPP
#define NOTNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class NotNode : public AstNode {
   public:
    NotNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
    std::shared_ptr<AstNode> getChildNode() { return childNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<AstNode> childNode;
};

#endif