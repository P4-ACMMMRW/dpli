#ifndef NOTNODE_HPP
#define NOTNODE_HPP

#include <AstNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class NotNode : public AstNode {
   public:
    NotNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};
    std::shared_ptr<AstNode> getchild() { return child; };

    void addChild(std::shared_ptr<AstNode> node) override;

    void print(std::string indent, std::string prefix) override;

   private:
    std::shared_ptr<AstNode> child = nullptr;
};

#endif