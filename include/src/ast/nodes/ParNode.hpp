#ifndef PARNODE_HPP
#define PARNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class ParNode : public AstNode {
   public:
    ParNode(AstNode* parent) : AstNode(parent) {}
    AstNode* getChildNode() { return childNode; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* childNode = nullptr;
};

#endif