#ifndef PARNODE_HPP
#define PARNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ParNode : public AstNode {
    public:
     ParNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
     std::shared_ptr<AstNode> getChildNode() { return childNode; };

     void addChild(std::shared_ptr<AstNode> node) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> childNode = nullptr;
};

#endif