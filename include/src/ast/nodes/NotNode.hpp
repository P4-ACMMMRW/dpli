#ifndef NOTNODE_HPP
#define NOTNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class NotNode : public AstNode {
   public:
    NotNode(AstNode* parent) : AstNode(parent){};
    AstNode* getchild() { return child; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* child = nullptr;
};

#endif