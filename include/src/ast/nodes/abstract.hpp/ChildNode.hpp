#ifndef CHILDNODE_HPP
#define CHILDNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ChildNode : public AstNode {
   public:
    ChildNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
    
    std::shared_ptr<AstNode> getChildNode() { return childNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;


   private:
    std::shared_ptr<AstNode> childNode;
};

#endif