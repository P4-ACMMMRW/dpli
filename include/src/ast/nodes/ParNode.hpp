#ifndef PARNODE_HPP
#define PARNODE_HPP

#include <UnaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class ParNode : public UnaryNode {
   public:
    ParNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif