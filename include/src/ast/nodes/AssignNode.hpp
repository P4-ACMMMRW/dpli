#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <BinaryNode.hpp>

class AssignNode : public BinaryNode {
   public:
    AssignNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif