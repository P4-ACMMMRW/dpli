#ifndef PROGNODE_HPP
#define PROGNODE_HPP

#include <string>
#include <vector>
#include <AstNode.hpp>
#include <iostream>

class ProgNode : public AstNode {
public:
    std::vector<AstNode*> getChildren()                     { return children; };
    void                  addChild(AstNode* child) override;

    void print(std::string indent, std::string prefix) override ;
private:
    std::vector<AstNode*> children;
};

#endif