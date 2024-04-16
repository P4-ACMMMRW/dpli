#ifndef HEADERINDEXNODE_HPP
#define HEADERINDEXNODE_HPP

#include <BinaryNode.hpp>

class HeaderIndexNode : public BinaryNode {
   public:
    HeaderIndexNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif