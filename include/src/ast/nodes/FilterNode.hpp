#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

#include <BinaryNode.hpp>

class FilterNode : public BinaryNode {
   public:
    FilterNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<FilterNode>(shared_from_this()));
    };
};

#endif