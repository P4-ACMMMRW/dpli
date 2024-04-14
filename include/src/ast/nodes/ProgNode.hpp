#ifndef PROGNODE_HPP
#define PROGNODE_HPP

#include <AstNode.hpp>
#include <AstVisitor.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class ProgNode : public AstNode {
   public:
    std::vector<std::shared_ptr<AstNode>> getChildNodes() { return children; };
    void addChild(std::shared_ptr<AstNode> child) override;

    void print(std::string indent, std::string prefix) override;

    void accept(AstVisitor* visitor) override;

   private:
    std::vector<std::shared_ptr<AstNode>> children;
};

#endif