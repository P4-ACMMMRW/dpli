#ifndef HEADERINDEXNODE_HPP
#define HEADERINDEXNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class HeaderIndexNode : public BinaryNode {
   public:
    HeaderIndexNode(std::shared_ptr<AstNode> parent) : AstNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif