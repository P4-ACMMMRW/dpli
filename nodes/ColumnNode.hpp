#ifndef COLUMNNODE_HPP
#define COLUMNNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <string>
#include <vector>

class ColumnNode : public AstNode {
   public:
    ColumnNode(AstNode* parent) : AstNode(parent){};
    AstNode* getchild() { return child; };

    void addChild(AstNode* node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    AstNode* child = nullptr;
};

#endif