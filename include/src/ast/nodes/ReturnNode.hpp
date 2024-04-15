#ifndef RUTURNNODE_HPP
#define RUTURNNODE_HPP

#include <UnaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ReturnNode : public UnaryNode {
   public:
    ReturnNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif