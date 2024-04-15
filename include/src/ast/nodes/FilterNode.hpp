#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class FilterNode : public BinaryNode {
   public:
    FilterNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif