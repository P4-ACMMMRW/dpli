#ifndef RUTURNNODE_HPP
#define RUTURNNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ReturnNode : public AstNode {
    public:
     ReturnNode(std::shared_ptr<AstNode> parent) : AstNode(parent){};
     std::shared_ptr<AstNode> getchild() { return child; };

     void addChild(std::shared_ptr<AstNode> node) override;

     void print(std::string indent, std::string prefix) override;

    private:
     std::shared_ptr<AstNode> child = nullptr;
};

#endif