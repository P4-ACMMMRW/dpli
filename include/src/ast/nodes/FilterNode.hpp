#ifndef FILTERNODE_HPP
#define FILTERNODE_HPP

#include "IndexNode.hpp"

class FilterNode : public IndexNode {
   public:
    FilterNode(std::shared_ptr<AstNode> parent) : IndexNode(std::move(parent)) {}

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<FilterNode>(shared_from_this()));
    };
};

#endif