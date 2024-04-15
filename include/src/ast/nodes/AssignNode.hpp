#ifndef ASSIGNNODE_HPP
#define ASSIGNNODE_HPP

#include <BinaryNode.hpp>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

class AssignNode : public BinaryNode {
   public:
    AssignNode(std::shared_ptr<AstNode> parent) { AstNode::setParent(std::move(parent)); }

    void accept(std::shared_ptr<AstVisitor> visitor) override;
};

#endif