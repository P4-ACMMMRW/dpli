#ifndef UNARYEXPRNODE_HPP
#define UNARYEXPRNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class UnaryExprNode : public AstNode {
    public:
     UnaryExprNode(std::shared_ptr<AstNode> parent) : AstNode(parent) {}
     std::shared_ptr<AstNode> getchild() { return child; };

     void addChild(std::shared_ptr<AstNode> child) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> child = nullptr;
};

#endif