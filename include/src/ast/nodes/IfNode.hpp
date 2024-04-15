#ifndef IFNODE_HPP
#define IFNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class IfNode : public AstNode {
   public:
    IfNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
    std::shared_ptr<AstNode> getCondNode() { return condNode; };
    std::vector<std::shared_ptr<AstNode>> getBodyNodes() { return bodyNodes; };
    std::shared_ptr<AstNode> getElseNode() { return elseNode; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

    void accept(std::shared_ptr<AstVisitor> visitor) override;

   private:
    std::shared_ptr<AstNode> condNode;
    std::vector<std::shared_ptr<AstNode>> bodyNodes;
    std::shared_ptr<AstNode> elseNode;
};

#endif