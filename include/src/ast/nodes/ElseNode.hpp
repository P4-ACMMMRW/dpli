#ifndef ELSENODE_HPP
#define ELSENODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ElseNode : public AstNode {
    public:
     ElseNode(std::shared_ptr<AstNode> parent) : AstNode(parent){};
     std::vector<std::shared_ptr<AstNode>>& getBodyNodes() { return bodyNodes; };

     void addChild(std::shared_ptr<AstNode> node);

     void print(std::string indent, std::string prefix) override;

    private:
     std::vector<std::shared_ptr<AstNode>> bodyNodes;
};

#endif