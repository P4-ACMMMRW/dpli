#ifndef COLUMNNODE_HPP
#define COLUMNNODE_HPP

#include "BinaryNode.hpp"

class ColumnNode : public BinaryNode {
   public:
    ColumnNode(std::shared_ptr<AstNode> parent) : BinaryNode(std::move(parent)){};

    void accept(std::shared_ptr<AstVisitor> visitor) override {
        visitor->visit(std::static_pointer_cast<ColumnNode>(shared_from_this()));
    };
};

#endif