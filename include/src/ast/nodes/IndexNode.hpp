#ifndef INDEXNODE_HPP
#define INDEXNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class IndexNode : public BinaryNode {
   public:
    IndexNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif