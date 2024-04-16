#ifndef INDEXNODE_HPP
#define INDEXNODE_HPP

#include <BinaryNode.hpp>

class IndexNode : public BinaryNode {
   public:
    IndexNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif